// Copyright Epic Games, Inc. All Rights Reserved.

#include "TimeWarpGameMode.h"
#include "TimeWarpHUD.h"
#include "TimeWarpCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATimeWarpGameMode::ATimeWarpGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATimeWarpHUD::StaticClass();
}
