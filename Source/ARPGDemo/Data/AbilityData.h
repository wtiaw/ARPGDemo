// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityData.generated.h"

USTRUCT(BlueprintType)
struct FAbilityData
{
	GENERATED_BODY()

	/**
	 * @brief 技能名称
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString AbilityName;

	/**
	 * @brief 技能描述
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString AbilityDescription;

	/**
	 * @brief 技能图标
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UTexture2D* AbilityIcon;

	FAbilityData();

	FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* AbilityIcon);
};
