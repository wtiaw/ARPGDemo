// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySetBase.h"
#include "GameplayEffectExtension.h"

UAbilitySetBase::UAbilitySetBase()
	: MaxHealth(1)
	, Health(1)
{
}

void UAbilitySetBase::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Level, MaxLevel, NewValue, GetLevelAttribute());
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
		AdjustAttributeForMaxChange(XP, MaxXP, NewValue, GetXPAttribute());
	}
}

void UAbilitySetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if(Data.EvaluatedData.Attribute == GetLevelAttribute())
	{
		SetLevel(FMath::Clamp(GetLevel(),1.f,GetMaxLevel()));
	}
	if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(),0.f,GetMaxHealth()));
	}
	if(Data.EvaluatedData.Attribute == GetXPAttribute())
	{
		SetXP(FMath::Clamp(GetXP(),0.f,GetMaxXP()));
	}
}

void UAbilitySetBase::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}