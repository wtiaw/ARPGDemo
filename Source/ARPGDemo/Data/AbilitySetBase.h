// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 基础属性集
 */
UCLASS()
class ARPGDEMO_API UAbilitySetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAbilitySetBase();
	
	/**
	 * @brief 当前等级
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Level")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UAbilitySetBase, Level);

	/**
	 * @brief 最大等级
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Level")
	FGameplayAttributeData MaxLevel;
	ATTRIBUTE_ACCESSORS(UAbilitySetBase, MaxLevel);
	
	/**
	 * @brief 最大生命值
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAbilitySetBase, MaxHealth);

	/**
	 * @brief 当前生命值
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAbilitySetBase, Health);

	/**
	 * @brief 当前经验值
	 */
	UPROPERTY(BlueprintReadOnly, Category = "XP")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(UAbilitySetBase, XP);

	/**
	 * @brief 最大经验值
	 */
	UPROPERTY(BlueprintReadOnly, Category = "XP")
	FGameplayAttributeData MaxXP;
	ATTRIBUTE_ACCESSORS(UAbilitySetBase, MaxXP);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
