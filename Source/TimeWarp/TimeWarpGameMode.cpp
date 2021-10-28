// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpGameMode.h"
#include "TimeWarpHUD.h"
#include "TimeWarpCharacter.h"
#include "TimeWarpGameState.h"
#include "TimeWarpPlayerStart.h"
#include "TimeWarpPlayerController.h"

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
}

void ATimeWarpGameMode::PostLogin(APlayerController* NewPlayer)
{
	static_cast<ATimeWarpPlayerController*>(NewPlayer)->ClientPostLogin();
}

void ATimeWarpGameMode::RespawnPlayerEvent_Implementation()
{
	// TODO: finish implementing
	
	// TODO: why is this not working? It was set in the level blueprint...
	if (IsValid(playerStart1) && IsValid(playerStart2))
	{
		FString debugMessage = FString::Printf(TEXT("Debug: Found player start actors"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
	}

	FString debugMessage = FString::Printf(TEXT("TODO: need to spawn players at start locations"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, debugMessage);
}
