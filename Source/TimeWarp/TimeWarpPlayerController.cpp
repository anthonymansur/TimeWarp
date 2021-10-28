// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWarpPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimeWarpGameMode.h"

void ATimeWarpPlayerController::ClientPostLogin()
{
	// Setup Ingame UI

	// call Game Mode's respawn player event
	static_cast<ATimeWarpGameMode*>(
		UGameplayStatics::GetGameMode(GetWorld()))->RespawnPlayerEvent();
}