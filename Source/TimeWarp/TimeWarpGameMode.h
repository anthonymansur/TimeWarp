// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <random>

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TimerManager.h"

#include "TimeWarpGameMode.generated.h"

UCLASS(minimalapi)
class ATimeWarpGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATimeWarpGameMode();

public:
	/** Server function for spawning projectiles. */
	UFUNCTION(Server, Reliable)
	void RespawnPlayerEvent(APlayerController* NewPlayer);

	// Funciton for spawning ammunitions
	void SpawnAmmunitions(int num_ammunitions);

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void HandleMatchHasStarted() override;
	void EndElimination();

protected:
	AActor* playerStart1;
	AActor* playerStart2;
	APlayerController* player1Controller;
	APlayerController* player2Controller;
	TSubclassOf<APawn> playerClass;

	FTimerHandle handle_gameStarting;
	FTimerHandle handle_pathSelection;
	FTimerHandle handle_pathSelectionEnd;
	FTimerHandle handle_lighting;
	FTimerHandle handle_preelimination;
	FTimerHandle handle_elimination;
	FTimerHandle handle_eliminationEnd;

	TArray<FVector>* p1PositionOverTime;
	TArray<FVector>* p2PositionOverTime;
	int positionIndex;
	int positionArraySize;

	TSubclassOf<AActor> PathLineClass;
	TArray<AActor*> Lines;
	
	// For random number generation
	std::default_random_engine generator;
	TArray<FVector> ammunitionPositions;
	TSubclassOf<AActor> ammunitionBPClass;

protected:
	void StartPathSelection();
	void EndPathSelection();
	void StartLightingStage();
	void EndLightingStage();
	void PreEliminationStage();
	void StartEliminationStage();

	void StorePlayerPositions();
	void TranslatePlayerPositions();
};



