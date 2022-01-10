// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Avoid.h"

FName UGameplayAbility_Avoid::GetAvoidDirection(APlayerCharacter* PlayerCharacter)
{
	FString Direction;

	const FVector2D MoveAxis = PlayerCharacter->GetMoveAxis();
	if (MoveAxis.Y < 0)
	{
		Direction = TEXT("AvoidLeft");
	}
	else if (MoveAxis.Y > 0)
	{
		Direction = TEXT("AvoidRight");
	}
	else if (MoveAxis.X <= 0)
	{
		Direction = TEXT("AvoidBack");
	}
	else if (MoveAxis.X > 0)
	{
		Direction = TEXT("AvoidFront");
	}

	return FName(Direction);
}
