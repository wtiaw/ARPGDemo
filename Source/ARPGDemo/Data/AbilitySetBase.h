// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/NoExportTypes.h"
#include "AbilitySetBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UAbilitySetBase : public UObject
{
	GENERATED_BODY()

	/**
	 * @brief 最大生命值
	 */
	FGameplayAttributeData MaxHealth;

	/**
	 * @brief 当前生命值
	 */
	FGameplayAttributeData CurrentHealth;
};
