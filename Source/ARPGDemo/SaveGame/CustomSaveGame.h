// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/Data/AbilityData.h"
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
	UPROPERTY(BlueprintReadWrite)
	TMap<int,int> LevelMaps;

	UPROPERTY(BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite)
	float Health;

	UPROPERTY(BlueprintReadWrite)
	float Level;

	UPROPERTY(BlueprintReadWrite)
	TMap<int, int> SkillDatas;
};
