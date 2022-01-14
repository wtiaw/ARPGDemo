// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/GamePlayAbilitySystem/GameplayAbility/GA/GameplayAbility_Base.h"
#include "AbilityData.generated.h"

/**
 * @brief 技能类型
 */
UENUM(BluePrintType)
enum class EAbilityType : uint8
{
	/**
	 * @brief 无
	 */
	None,

	/**
	 * @brief 主动技能
	 */
	ActiveSkill,

	/**
	 * @brief 被动技能
	 */
	Passive,
};

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

	/**
	 * @brief 技能等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int Level;

	/**
	 * @brief GAS标签
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FGameplayTagContainer Tags;
	
	/**
	 * @brief GA类
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<UGameplayAbility_Base> Ability;

	FAbilityData();

	FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* AbilityIcon, int Level, FGameplayTagContainer Tags, TSubclassOf<UGameplayAbility_Base> Ability);

	bool bIsValid();
};
