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
	Positive,

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
	 * @brief 激活时的技能图标
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UTexture2D* ActivatedIcon;

	/**
	 * @brief 未激活时的技能图标
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UTexture2D* InactivatedAbilityIcon;
	
	/**
	 * @brief 技能种类
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EAbilityType AbilityType;
	
	/**
	 * @brief 技能等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int Level;

	/**
	 * @brief 最大技能等级
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	int MaxLevel;
	
	/**
	 * @brief GA类
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TSubclassOf<UGameplayAbility_Base> Ability;

	/**
	 * @brief GAS标签
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FGameplayTagContainer Tags;

	FAbilityData();

	FAbilityData(FString AbilityName, FString AbilityDescription, UTexture2D* ActivatedAbilityIcon, UTexture2D* InactivatedAbilityIcon,
					EAbilityType AbilityType, int Level, int MaxLevel, TSubclassOf<UGameplayAbility_Base> Ability, FGameplayTagContainer Tags);

	bool IsValid();
};
