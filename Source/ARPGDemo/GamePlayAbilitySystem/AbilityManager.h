// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "ARPGDemo/Data/Enum/EGASAbilityInputID.h"
#include "GameplayAbility/GA/GameplayAbility_Base.h"
#include "UObject/NoExportTypes.h"
#include "AbilityManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UAbilityManager : public UObject
{
	GENERATED_BODY()

private:
	static UAbilityManager* Instance;

	TMap<EGASAbilityInputID,FGameplayAbilitySpecHandle> ActiveAbility;
	
public:
	static UAbilityManager* GetInstance();

	void GiveAbility(EGASAbilityInputID GASAbilityInputID, TSubclassOf<UGameplayAbility_Base> AbilityClass, int Level);

	void SwapAbility(EGASAbilityInputID Source, EGASAbilityInputID Target);

	void ClearAbility(EGASAbilityInputID GASAbilityInputID);

private:
	UAbilitySystemComponent* GetGASComponent() const;
};
