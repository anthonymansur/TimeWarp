// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpGameMode.h"
#include "TimeWarpHUD.h"
#include "TimeWarpCharacter.h"
#include "TimeWarpGameState.h"
#include "TimeWarpPlayerController.h"
#include "TimeWarpPlayerState.h"
#include "Engine/LevelScriptActor.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

#include <algorithm>

#define RECORD_FREQUENCY 0.002 // in seconds
#define PREGAME_LENGTH 5.0
#define GAME_LENGTH 15.0

#define RANDOM_SEED 123456
#define NUM_AMMUNITIONS 100

ATimeWarpGameMode::ATimeWarpGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
	playerClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATimeWarpHUD::StaticClass();

	// use our custom game state class
	GameStateClass = ATimeWarpGameState::StaticClass();

	// use our custom player controllers
	PlayerControllerClass = ATimeWarpPlayerController::StaticClass();

	// use our custom player state
	PlayerStateClass = ATimeWarpPlayerState::StaticClass();

	// Locate the player start locations
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PlayerStart", actors);

	if (actors.Num() == 2)
	{
		playerStart1 = actors[0];
		playerStart2 = actors[1];

	}

	positionIndex = 0;

	static ConstructorHelpers::FClassFinder<AActor> LineClassFinder(TEXT("/Game/Line"));
	PathLineClass = LineClassFinder.Class;
	
	// Initialize the random number generator
	generator = std::default_random_engine(RANDOM_SEED);
	static ConstructorHelpers::FClassFinder<AActor> AmmunitionBPClassFinder(TEXT("/Game/AmmunitionBP"));
	ammunitionBPClass = AmmunitionBPClassFinder.Class;
}

void ATimeWarpGameMode::PostLogin(APlayerController* NewPlayer)
{
	static_cast<ATimeWarpPlayerController*>(NewPlayer)->ClientPostLogin(NewPlayer);
}

void ATimeWarpGameMode::SpawnAmmunitions(int num_ammunitions) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, "ATimeWarpGameMode::SpawnAmmunitions is being called");

	const float mean = 0.0f;
	const float stddev = 0.35f;

	const FVector offset = FVector(-282.f, 0.f, 0.f);
	const float scale = 850.0f;
	std::normal_distribution<float> distribution(mean, stddev);
	for (int i = 0; i < num_ammunitions; i++) {
		const float x = distribution(generator) * scale;
		const float y = distribution(generator) * scale;
		const FVector SpawnLocation = FVector(x, y, 170.0f) + offset;
		const FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
		FActorSpawnParameters ActorSpawnParams;
		AActor* ammo = GetWorld()->SpawnActor<AActor>(ammunitionBPClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		ammunitionPositions.Emplace(SpawnLocation);
	}
}

void ATimeWarpGameMode::RespawnPlayerEvent_Implementation(APlayerController* NewPlayer)
{	
	// TODO: figure out rotation respawn bug

	// Find out which player connected
	int serverPlayerId = GameState->PlayerArray[0]->GetPlayerId();
	int controllerPlayerId = NewPlayer->PlayerState->GetPlayerId();

	if (serverPlayerId == controllerPlayerId)
	{
		// Spawn ammunitions on the server
		SpawnAmmunitions(NUM_AMMUNITIONS);

		// server
		player1Controller = NewPlayer;

		if (IsValid(playerStart1))
		{
			const FRotator SpawnRotation = playerStart1->GetActorRotation();
			const FVector SpawnLocation = playerStart1->GetActorLocation();

			FActorSpawnParameters ActorSpawnParams;

			// spawn character
			APawn* player1 = GetWorld()->SpawnActor<APawn>(
				playerClass,
				SpawnLocation, 
				SpawnRotation, 
				ActorSpawnParams);

			// Posses character
			NewPlayer->Possess(player1);
			static_cast<ATimeWarpPlayerController*>(NewPlayer)->ForceControlRotation(SpawnRotation);
			NewPlayer->ClientSetHUD(HUDClass);

			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Waiting for other player to join.");
		}
	}
	else
	{
		// client
		player2Controller = NewPlayer;

		if (IsValid(playerStart2))
		{
			const FRotator SpawnRotation = playerStart2->GetActorRotation();
			const FVector SpawnLocation = playerStart2->GetActorLocation();

			FActorSpawnParameters ActorSpawnParams;

			// spawn character
			APawn* player2 = GetWorld()->SpawnActor<APawn>(
				playerClass,
				SpawnLocation,
				SpawnRotation,
				ActorSpawnParams);

			// Posses character
			NewPlayer->Possess(player2);
			static_cast<ATimeWarpPlayerController*>(NewPlayer)->ForceControlRotation(SpawnRotation);
			NewPlayer->ClientSetHUD(HUDClass);

			// Start Match
			StartMatch();
		}
	}
}

void ATimeWarpGameMode::HandleMatchHasStarted()
{
	p1PositionOverTime = static_cast<ATimeWarpGameState*>(GameState)->getP1Position();
	p2PositionOverTime = static_cast<ATimeWarpGameState*>(GameState)->getP2Position();

	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowRotation();
	}

	GEngine->AddOnScreenDebugMessage(-1, PREGAME_LENGTH - 0.5f, FColor::Blue, "Match will begin shortly.");

	GetWorldTimerManager().SetTimer(handle_gameStarting, this, &ATimeWarpGameMode::StartPathSelection, PREGAME_LENGTH, false, -1.f);
}

void ATimeWarpGameMode::StartPathSelection()
{

	// TODO: Store players' translation into buffer
	//bool eventFound = GetLevel()->GetLevelScriptActor()->RemoteEvent("PathSelection");
	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowTranslation();
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Path Selection started!");

	GetWorldTimerManager().SetTimer(handle_pathSelection, this, &ATimeWarpGameMode::StorePlayerPositions, RECORD_FREQUENCY, true, 0.f);
	GetWorldTimerManager().SetTimer(handle_pathSelectionEnd, this, &ATimeWarpGameMode::EndPathSelection, GAME_LENGTH, false, -1.f);
}

void ATimeWarpGameMode::EndPathSelection()
{
	// TODO: implement
	// 1. Unpossess pawns and delete from map
	// 2. Do any preinitialization for lighting
	// 3. Start lighting phase

	// Skipping the lighting phase for development purposes

	// Invalidate path selection timers
	GetWorldTimerManager().ClearTimer(handle_pathSelection);

	positionArraySize = std::min(p1PositionOverTime->Num(), p2PositionOverTime->Num());


	PreEliminationStage();
}

void ATimeWarpGameMode::StartLightingStage()
{
	// TODO: implement
}
void ATimeWarpGameMode::EndLightingStage()
{
	// TODO: implement
}

void ATimeWarpGameMode::PreEliminationStage()
{
	TranslatePlayerPositions();

	int i = 0;
	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->DisableTranslation();
		if (i == 0)
			static_cast<ATimeWarpPlayerController*>(pawn->GetController())->ForceControlRotation(playerStart1->GetActorRotation());
		else
			static_cast<ATimeWarpPlayerController*>(pawn->GetController())->ForceControlRotation(playerStart2->GetActorRotation());
		if (i == 0)
			pawn->SendPositionArray(true);
		else
			pawn->SendPositionArray(false);
		i++;
	}

	GEngine->AddOnScreenDebugMessage(-1, PREGAME_LENGTH - 0.5f, FColor::Blue, "Elimination will begin shortly.");

	GetWorldTimerManager().SetTimer(handle_preelimination, this, &ATimeWarpGameMode::StartEliminationStage, PREGAME_LENGTH, false, -1.f);
}

void ATimeWarpGameMode::StartEliminationStage()
{

	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowShooting();
	}

	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, "Elimination started!");

	GetWorldTimerManager().SetTimer(handle_elimination, this, &ATimeWarpGameMode::TranslatePlayerPositions, RECORD_FREQUENCY, true, 0.f);
	GetWorldTimerManager().SetTimer(handle_eliminationEnd, this, &ATimeWarpGameMode::EndElimination, GAME_LENGTH, false, -1.f);

	// set the draw commands for each player here 
	/*for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->StartDrawPathCommand();
	}*/
	for (int i = 0; i < 2; i++)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(UGameplayStatics::GetPlayerPawn(GetWorld(), i));
		pawn->StartDrawPathCommand();
	}
}


void ATimeWarpGameMode::EndElimination()
{
	// invalidate elimination timer
	GetWorldTimerManager().ClearTimer(handle_elimination);
	GetWorldTimerManager().ClearTimer(handle_eliminationEnd); // For when this function is called prematurely

	bool player1Dead = false; 
	bool player2Dead = false;
	for (int i = 0; i < 2; i++)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(UGameplayStatics::GetPlayerPawn(GetWorld(), i));
		if (pawn->IsDead())
		{
			pawn->DisableRotation();
			if (i == 0)
			{
				player1Dead = true;
			}
			else
			{
				player2Dead = true;
			}
		}
		pawn->DisableTranslation();
		pawn->DisableShooting();

		pawn->EndDrawpathCommand();
	}

	FString debug;
	if (player2Dead)
		debug = FString::Printf(TEXT("Player 1 won!"));
	else if (player1Dead)
		debug = FString::Printf(TEXT("Player 2 won!"));
	else
		debug = FString::Printf(TEXT("Draw!"));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Match ended");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, debug);
}

void ATimeWarpGameMode::StorePlayerPositions()
{
	FVector p1Pos = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	FVector p2Pos = UGameplayStatics::GetPlayerPawn(GetWorld(), 1)->GetActorLocation();

	p1PositionOverTime->Emplace(p1Pos);
	p2PositionOverTime->Emplace(p2Pos);
}
void ATimeWarpGameMode::TranslatePlayerPositions()
{
	if (positionIndex < positionArraySize)
	{
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorLocation((*p1PositionOverTime)[positionIndex]);
		UGameplayStatics::GetPlayerPawn(GetWorld(), 1)->SetActorLocation((*p2PositionOverTime)[positionIndex]);
	}

	//DrawPaths();
	
	positionIndex++;
}

// helper function
void ATimeWarpGameMode::DrawSinglePath(int i)
{
	if ((i + 10) >= p1PositionOverTime->Num())
		return;
	FVector posDiff = FVector((*p1PositionOverTime)[i + 10]) - FVector((*p1PositionOverTime)[i]);
	posDiff[2] = 0;
	float angle = FMath::Acos(FVector::DotProduct(FVector(1, 0, 0), posDiff.GetSafeNormal()));
	FTransform transform1 = FTransform();
	transform1.SetLocation(FVector((*p1PositionOverTime)[i].X, (*p1PositionOverTime)[i].Y, 171));
	transform1.SetRotation(FQuat(0, 0, 1, angle));
	//transform1.SetScale3D(FVector(10, 0.1, 1));

	posDiff = FVector((*p2PositionOverTime)[i + 1]) - FVector((*p2PositionOverTime)[i]);
	posDiff[2] = 0;
	angle = 0;// FMath::Acos(FVector::DotProduct(FVector(1, 0, 0), posDiff.GetSafeNormal()));
	FTransform transform2 = FTransform();
	transform2.SetLocation(FVector((*p2PositionOverTime)[i].X, (*p2PositionOverTime)[i].Y, 171));
	transform2.SetRotation(FQuat(0, 0, 1, angle));
	transform2.SetScale3D(FVector(posDiff.Size(), 0.1, 1));


	FActorSpawnParameters ActorSpawnParams;
	Lines.Add(GetWorld()->SpawnActor<AActor>(PathLineClass, transform1, ActorSpawnParams));
	Lines.Last()->SetActorScale3D(FVector(0.1, 2, 1));
	Lines.Add(GetWorld()->SpawnActor<AActor>(PathLineClass, transform2, ActorSpawnParams));
}

void ATimeWarpGameMode::DrawPaths()
{
	static const float drawInterval = RECORD_FREQUENCY; // interval, in seconds, to draw line 
	static const float drawLength = 0.5; // draw the path one second ahead 
	static const int numOfLinesToDraw = 2 * (int)(drawLength / drawInterval);

	if (Lines.Num() == 0)
	{
		for (int i = 0; i < numOfLinesToDraw; i++)
		{
			DrawSinglePath(i);
		}
	}
	else
	{
		Lines[0]->Destroy();
		Lines[1]->Destroy();
		Lines.RemoveAt(0, 2); // remove first line 
		if ((positionIndex + numOfLinesToDraw) < (p1PositionOverTime->Num() - 1))
			DrawSinglePath(positionIndex + numOfLinesToDraw);
	}

	// delete all lines, if any 
	/*for (AActor* line : Lines)
	{
		line->Destroy();

	}
	Lines.Empty();*/


}

float ATimeWarpGameMode::getRecordFrequency()
{
	return (float) RECORD_FREQUENCY;
}