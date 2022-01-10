// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ARPGDemo/Character/Player/PlayerCharacter.h"
#include "ARPGDemo/Data/AbilityData.h"
#include "GameplayAbility_Avoid.generated.h"

/**
 * 闪避技能
 */
UCLASS()
class ARPGDEMO_API UGameplayAbility_Avoid : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* Avoid;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FAbilityData AbilityData;
	
public:
	UFUNCTION(BlueprintCallable)
	FName GetAvoidDirection(APlayerCharacter* PlayerCharacter);
};
