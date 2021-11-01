// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpGameMode.h"
#include "TimeWarpHUD.h"
#include "TimeWarpCharacter.h"
#include "TimeWarpGameState.h"
#include "TimeWarpPlayerController.h"
#include "TimeWarpPlayerState.h"

#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

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
		}

		// Start Match
		StartMatch();
	}
}

void ATimeWarpGameMode::HandleMatchHasStarted()
{
	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowRotation();
	}

	GetWorldTimerManager().SetTimer(timeHandle, this, &ATimeWarpGameMode::StartPathSelection, 5.f, false, -1.f);
}

void ATimeWarpGameMode::StartPathSelection()
{
	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowTranslation();
	}

	// TODO: Store players' translation into buffer

	GetWorldTimerManager().SetTimer(timeHandle, this, &ATimeWarpGameMode::EndPathSelection, 15.f, false, -1.f);
}

void ATimeWarpGameMode::EndPathSelection()
{
	// TODO: implement
	// 1. Unpossess pawns and delete from map
	// 2. Do any preinitialization for lighting
	// 3. Start lighting phase

	// Skipping the lighting phase for development purposes

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
	// TODO: implement

	for (APlayerState* Player : GameState->PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowShooting();
	}
}
void ATimeWarpGameMode::EndElimination()
{
	// TODO: implement
}
