// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Base.h"
#include "ARPGDemo/Character/Player/PlayerCharacter.h"
#include "GameplayAbility_Avoid.generated.h"

/**
 * 闪避技能
 */
UCLASS()
class ARPGDEMO_API UGameplayAbility_Avoid : public UGameplayAbility_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* Avoid;
	
public:
	UFUNCTION(BlueprintCallable)
	FName GetAvoidDirection(APlayerCharacter* PlayerCharacter);
};
