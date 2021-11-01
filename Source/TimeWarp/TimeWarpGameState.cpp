// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWarpGameState.h"
#include "TimeWarpGameMode.h"
#include "TimeWarpCharacter.h"
#include "TimeWarpPlayerState.h"

void ATimeWarpGameState::HandleMatchHasStarted()
{
	for (APlayerState* Player : PlayerArray)
	{
		ATimeWarpCharacter* pawn = static_cast<ATimeWarpCharacter*>(Player->GetPawn());
		pawn->AllowRotation();
	}
}