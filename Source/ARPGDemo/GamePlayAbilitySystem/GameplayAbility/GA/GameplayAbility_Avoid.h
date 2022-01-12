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
	/**
	 * @brief 需要播放的蒙太奇
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* Avoid;
	
public:
	/**
	 * @brief 得到玩家闪避的方向
	 * @return 方向
	 */
	UFUNCTION(BlueprintCallable)
	FName GetAvoidDirection(APlayerCharacter* PlayerCharacter);

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
