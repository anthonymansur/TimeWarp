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

USTRUCT(BlueprintType)
struct FScore
{
	GENERATED_BODY();
	UPROPERTY(BlueprintReadOnly)
	int player1;
	UPROPERTY(BlueprintReadOnly)
	int player2;
	UPROPERTY(BlueprintReadOnly)
	int winScore; // best 3 out of 5?
};

/**
 * 
 */
UCLASS()
class TIMEWARP_API ATimeWarpGameState : public AGameState
{
	GENERATED_BODY()
	ATimeWarpGameState();
protected:
	UPROPERTY(replicated)
	TArray<FVector> p1PositionOverTime;
	UPROPERTY(replicated)
	TArray<FVector> p2PositionOverTime;
	UPROPERTY(BlueprintReadOnly, replicated)
	FScore Score;
public:
	TArray<FVector>* getP1Position();
	TArray<FVector>* getP2Position();

	FScore getScore();
	bool incrementScore(bool player1); // returns true if game is over
	void resetScore();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutlifetimeProps) const override;
};