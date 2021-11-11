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

#define RECORD_FREQUENCY 0.002 // NOTE: this is also defined in TimeWarpCharacter
#define PREGAME_LENGTH 3.0
#define GAME_LENGTH 30.0 // original is 30.0

#define RANDOM_SEED 123456
#define NUM_AMMUNITIONS 20

#define FLOOR_HEIGHT 170.f

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
	const float mean = 0.0f;
	const float stddev = .8f;

	const FVector offset = FVector(-282.f, 0.f, 0.f);
	const float scale = 850.0f;
	std::normal_distribution<float> distribution(mean, stddev);
	for (int i = 0; i < num_ammunitions; i++) {
		const float x = distribution(generator) * scale;
		const float y = distribution(generator) * scale;
		const FVector SpawnLocation = FVector(x, y, FLOOR_HEIGHT + 20.0f) + offset;
		const FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);
		FActorSpawnParameters ActorSpawnParams;
		AActor* ammo = GetWorld()->SpawnActor<AActor>(ammunitionBPClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		//ammunitionPositions.Emplace(SpawnLocation);
		ammunitions.Add(ammo);
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

	// Spawn ammunitions
	SpawnAmmunitions(NUM_AMMUNITIONS);

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
		pawn->SetTimeRemaining(GAME_LENGTH);
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

	// remove ammo from map
	for (AActor* ammo : ammunitions)
	{
		ammo->Destroy();
	}
	ammunitions.Empty();

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
	for (int i = 0; i < 2; i++)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(UGameplayStatics::GetPlayerPawn(GetWorld(), i));
		pawn->StartDrawPathCommand();
		pawn->SetTimeRemaining(GAME_LENGTH);
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

		pawn->EndDrawPathCommand();
	}

	FString debug;
	if (player2Dead)
		debug = FString::Printf(TEXT("Player 1 won!"));
	else if (player1Dead)
		debug = FString::Printf(TEXT("Player 2 won!"));
	else
		debug = FString::Printf(TEXT("Draw!"));
	GEngine->AddOnScreenDebugMessage(-1, PREGAME_LENGTH, FColor::Red, debug);


	bool end = false;
	if (player1Dead)
		end = static_cast<ATimeWarpGameState*>(GameState)->incrementScore(false);
	else if (player2Dead)
		end = static_cast<ATimeWarpGameState*>(GameState)->incrementScore(true);

	if (end)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Match ended");
	}
	else
	{
		GetWorldTimerManager().SetTimer(handle_gameStarting, this, &ATimeWarpGameMode::ResetRound, PREGAME_LENGTH, false, -1.f);
	}
}

void ATimeWarpGameMode::ResetRound()
{
	int i = 0;
	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->DisableTranslation();
		pawn->AllowRotation();
		if (i == 0)
		{
			pawn->SetActorLocation(playerStart1->GetActorLocation());
			static_cast<ATimeWarpPlayerController*>(pawn->GetController())->ForceControlRotation(playerStart1->GetActorRotation());
		}
		else
		{
			pawn->SetActorLocation(playerStart2->GetActorLocation());
			static_cast<ATimeWarpPlayerController*>(pawn->GetController())->ForceControlRotation(playerStart2->GetActorRotation());
		}

		pawn->SetCurrentAmmo(10);
		pawn->SetCurrentHealth(100);
		pawn->SetTimeRemaining(0);
		pawn->SetPositionIndex(0);
		i++;
	}

	p1PositionOverTime->Empty();
	p2PositionOverTime->Empty();
	positionIndex = 0;
	positionArraySize = 0;

	HandleMatchHasStarted();
}

void ATimeWarpGameMode::StorePlayerPositions()
{
	FVector p1Pos = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	FVector p2Pos = UGameplayStatics::GetPlayerPawn(GetWorld(), 1)->GetActorLocation();

	p1PositionOverTime->Emplace(p1Pos);
	p2PositionOverTime->Emplace(p2Pos);
}
/*
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
*/
void ATimeWarpGameMode::TranslatePlayerPositions()
{
	
	for (int i = 0; i < GameState->PlayerArray.Num(); i++)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(GameState->PlayerArray[i]->GetPawn());
		int currentPositionIndex = std::min(std::max(pawn->GetPositionIndex(), 0), positionArraySize - 1);

		if (i == 0)
		{
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorLocation((*p1PositionOverTime)[currentPositionIndex]);
		}
		else {
			UGameplayStatics::GetPlayerPawn(GetWorld(), 1)->SetActorLocation((*p2PositionOverTime)[currentPositionIndex]);
		}

		if (!pawn->GetIsTimeTraveling())
		{
			pawn->SetPositionIndex(currentPositionIndex + 1);
		}
	}
}