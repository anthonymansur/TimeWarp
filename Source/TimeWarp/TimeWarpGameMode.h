// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimeWarpGameMode.generated.h"

UCLASS(minimalapi)
class ATimeWarpGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATimeWarpGameMode();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* playerStart1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* playerStart2;

public:
	/** Server function for spawning projectiles. */
	UFUNCTION(Server, Reliable)
	void RespawnPlayerEvent(APlayerController* NewPlayer);

	virtual void PostLogin(APlayerController* NewPlayer) override;

};



