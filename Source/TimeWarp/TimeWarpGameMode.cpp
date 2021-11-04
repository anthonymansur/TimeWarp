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

#define RECORD_FREQUENCY 0.002 // in seconds
#define PREGAME_LENGTH 5.0
#define GAME_LENGTH 15.0 

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
}

void ATimeWarpGameMode::PostLogin(APlayerController* NewPlayer)
{
	static_cast<ATimeWarpPlayerController*>(NewPlayer)->ClientPostLogin(NewPlayer);
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
	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowRotation();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Match will begin shortly.");

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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Path Selection started!");

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

	positionArraySize = std::min(p1PositionOverTime.Num(), p2PositionOverTime.Num());

	StartEliminationStage();
}

void ATimeWarpGameMode::StartLightingStage()
{
	// TODO: implement
}
void ATimeWarpGameMode::EndLightingStage()
{
	// TODO: implement
}
void ATimeWarpGameMode::StartEliminationStage()
{

	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->DisableTranslation();
		pawn->AllowShooting();
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, "Elimination started!");

	GetWorldTimerManager().SetTimer(handle_elimination, this, &ATimeWarpGameMode::TranslatePlayerPositions, RECORD_FREQUENCY, true, 0.f);
	GetWorldTimerManager().SetTimer(handle_eliminationEnd, this, &ATimeWarpGameMode::EndElimination, GAME_LENGTH, false, -1.f);
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

	p1PositionOverTime.Emplace(p1Pos);
	p2PositionOverTime.Emplace(p2Pos);
}
void ATimeWarpGameMode::TranslatePlayerPositions()
{
	if (positionIndex < positionArraySize)
	{
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->SetActorLocation(p1PositionOverTime[positionIndex]);
		UGameplayStatics::GetPlayerPawn(GetWorld(), 1)->SetActorLocation(p2PositionOverTime[positionIndex]);
	}
	
	positionIndex++;
}