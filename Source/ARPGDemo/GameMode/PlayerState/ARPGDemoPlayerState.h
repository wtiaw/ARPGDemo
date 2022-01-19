// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ARPGDemo/Data/AbilityData.h"
#include "ARPGDemo/Data/AbilitySetBase.h"
#include "GameFramework/PlayerState.h"
#include "ARPGDemoPlayerState.generated.h"

USTRUCT(BlueprintType)
struct FIntArray
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<int> Indexs;
};

/**
 * 
 */
UCLASS()
class ARPGDEMO_API AARPGDemoPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AARPGDemoPlayerState();

	/**
	 * @brief GAS组件
	 */
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	/**
	 * @brief GAS 属性集
	 */
	UPROPERTY(BlueprintReadOnly)
	UAbilitySetBase* AbilitySetBase;

	/**
	 * @brief 玩家初始化技能
	 */
	TArray<TSubclassOf<UGameplayAbility_Base>> StartUpAbility;

	/**
	 * @brief 技能栏中技能
	 */
	TArray<FAbilityData> SkillBarAbilityDatas;
	
protected:
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

public:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAbilitySetBase* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState|Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|GDPlayerState")
	bool IsAlive() const;
};
