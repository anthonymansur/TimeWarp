// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TimeWarpGameState.generated.h"

enum RoundState
{
	WAITING = 0,
	PATH_SELECTION = 1,
	LIGHTING,
	ELIMINATION
};

struct FScore
{
	int player1;
	int player2;
	int winScore; // best 3 out of 5?
};

/**
 * 
 */
UCLASS()
class TIMEWARP_API ATimeWarpGameState : public AGameState
{
	GENERATED_BODY()

protected:
	virtual void HandleMatchHasStarted() override;

public:
};