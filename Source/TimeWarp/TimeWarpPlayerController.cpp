// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWarpPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimeWarpGameMode.h"

void ATimeWarpPlayerController::ClientPostLogin(APlayerController* NewPlayer)
{
	// Setup Ingame UI

	// call Game Mode's respawn player event
	static_cast<ATimeWarpGameMode*>(
		UGameplayStatics::GetGameMode(GetWorld()))->RespawnPlayerEvent(NewPlayer);
}

// From https://answers.unrealengine.com/questions/124855/what-can-change-the-rotation-of-a-newly-possessed.html 
void ATimeWarpPlayerController::ForceControlRotation(const FRotator& NewRotation)
{
    if (!HasAuthority())
    {
        // Just call SetControlRotation() on the client
        SetControlRotation(NewRotation);
        return;
    }

    // On server
    SetControlRotation(NewRotation);

    // Force on client
    ClientSetRotation(NewRotation);
}
