// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TimeWarpHUD.generated.h"

UCLASS()
class ATimeWarpHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATimeWarpHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

