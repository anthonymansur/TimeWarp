// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TimeWarpGameInstance.generated.h"

enum State
{
	STARTUP = 0,
	MAIN_MENU,
	PLAYING
};

/**
 * 
 */
UCLASS()
class TIMEWARP_API UTimeWarpGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UTimeWarpGameInstance();
};
