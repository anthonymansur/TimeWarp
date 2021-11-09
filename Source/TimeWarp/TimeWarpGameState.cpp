// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeWarpGameState.h"
#include "TimeWarpGameMode.h"
#include "TimeWarpCharacter.h"
#include "TimeWarpPlayerState.h"
#include "Net/UnrealNetwork.h"


ATimeWarpGameState::ATimeWarpGameState()
{
	Score.winScore = 3;
}

void ATimeWarpGameState::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATimeWarpGameState, p1PositionOverTime);
	DOREPLIFETIME(ATimeWarpGameState, p2PositionOverTime);
	DOREPLIFETIME(ATimeWarpGameState, Score);
}

TArray<FVector>* ATimeWarpGameState::getP1Position()
{
	return &p1PositionOverTime;
}

TArray<FVector>* ATimeWarpGameState::getP2Position()
{
	return &p2PositionOverTime;
}

FScore ATimeWarpGameState::getScore()
{
	return Score;
}
bool ATimeWarpGameState::incrementScore(bool player1)
{
	if (GetWorld()->GetAuthGameMode() == nullptr)
		return false;
	if (player1)
	{
		Score.player1 += 1;
		if (Score.player1 == Score.winScore)
			return true;
	}
	else
	{
		Score.player2 += 1;
		if (Score.player2 == Score.winScore)
			return true;
	}
	return false;
}
void ATimeWarpGameState::resetScore()
{
	Score.player1 = 0;
	Score.player2 = 0;
}
