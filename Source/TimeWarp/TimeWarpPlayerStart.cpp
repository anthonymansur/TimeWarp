// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWarpPlayerStart.h"

// Sets default values
ATimeWarpPlayerStart::ATimeWarpPlayerStart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeWarpPlayerStart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeWarpPlayerStart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

