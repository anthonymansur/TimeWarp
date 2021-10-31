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
	void ClientPostLogin(APlayerController* NewPlayer);

	// From https://answers.unrealengine.com/questions/124855/what-can-change-the-rotation-of-a-newly-possessed.html
/** Force the control rotation on client and server. */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn", meta = (Tooltip = "Set the control rotation."))
		virtual void ForceControlRotation(const FRotator& NewRotation);
};
