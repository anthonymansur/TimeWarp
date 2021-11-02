// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

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

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void HandleMatchHasStarted() override;
	void EndElimination();

protected:
	AActor* playerStart1;
	AActor* playerStart2;
	APlayerController* player1Controller;
	APlayerController* player2Controller;
	TSubclassOf<APawn> playerClass;

	FTimerHandle timeHandle;

protected:
	void StartPathSelection();
	void EndPathSelection();
	void StartLightingStage();
	void EndLightingStage();
	void StartEliminationStage();
};



