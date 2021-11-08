// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWarpGameState.h"
#include "TimeWarpGameMode.h"
#include "TimeWarpCharacter.h"
#include "TimeWarpPlayerState.h"
#include "Net/UnrealNetwork.h"


void ATimeWarpGameState::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATimeWarpGameState, p1PositionOverTime);
	DOREPLIFETIME(ATimeWarpGameState, p2PositionOverTime);
}

TArray<FVector>* ATimeWarpGameState::getP1Position()
{
	return &p1PositionOverTime;
}

TArray<FVector>* ATimeWarpGameState::getP2Position()
{
	return &p2PositionOverTime;
}