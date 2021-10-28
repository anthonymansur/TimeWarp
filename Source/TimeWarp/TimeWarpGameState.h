// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TimeWarpGameState.generated.h"

enum RoundState
{
	PATH_SELECTION = 0,
	LIGHTING,
	ELIMINATION
};

/**
 * 
 */
UCLASS()
class TIMEWARP_API ATimeWarpGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	RoundState roundState;
	
};