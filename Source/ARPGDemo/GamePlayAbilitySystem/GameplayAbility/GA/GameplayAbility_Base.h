// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ARPGDemo/Data/AbilityData.h"
#include "GameplayAbility_Base.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UGameplayAbility_Base : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/**
	 * @brief 技能数据
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FAbilityData AbilityData;

private:
	FTimerHandle CoolDownTimerHandle;
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void CoolDown();
};
