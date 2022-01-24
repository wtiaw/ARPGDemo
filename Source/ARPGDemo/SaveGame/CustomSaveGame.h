// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class ARPGDEMO_API UCustomSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TMap<int,int> LevelMaps;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Health;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Level;
};
