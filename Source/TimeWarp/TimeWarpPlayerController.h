// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TimeWarpPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TIMEWARP_API ATimeWarpPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// After login, set up the UI and spawn ther palyer
	void ClientPostLogin();
};
