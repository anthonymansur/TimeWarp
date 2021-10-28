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

	// use our custom HUD class
	HUDClass = ATimeWarpHUD::StaticClass();

	// use our custom game state class
	GameStateClass = ATimeWarpGameState::StaticClass();

	// use our custom player controllers
	PlayerControllerClass = ATimeWarpPlayerController::StaticClass();

	// use oru custom player state
	PlayerStateClass = ATimeWarpPlayerState::StaticClass();
}

void ATimeWarpGameMode::PostLogin(APlayerController* NewPlayer)
{
	static_cast<ATimeWarpPlayerController*>(NewPlayer)->ClientPostLogin(NewPlayer);
}

void ATimeWarpGameMode::RespawnPlayerEvent_Implementation(APlayerController* NewPlayer)
{
	// TODO: finish implementing
	
	// Find out which player connected
	int serverPlayerId = GameState->PlayerArray[0]->GetPlayerId();
	int controllerPlayerId = NewPlayer->PlayerState->GetPlayerId();

	if (serverPlayerId == controllerPlayerId)
	{
		// server
		FString debugMessage = FString::Printf(TEXT("Debug: I am the server%d"), controllerPlayerId);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
	}
	else
	{
		// client
		FString debugMessage = FString::Printf(TEXT("Debug: I am the client%d"), controllerPlayerId);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
	}

	// See if we have the player start actors on the map
	if (IsValid(playerStart1) && IsValid(playerStart2))
	{
		FString debugMessage = FString::Printf(TEXT("Debug: Player Starts properly connected!"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
	}

	FString debugMessage = FString::Printf(TEXT("TODO: need to spawn players at start locations"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
}
