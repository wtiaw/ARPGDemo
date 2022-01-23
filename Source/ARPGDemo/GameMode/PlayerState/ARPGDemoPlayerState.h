// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ARPGDemo/Data/AbilityData.h"
#include "ARPGDemo/Data/AbilitySetBase.h"
#include "GameFramework/PlayerState.h"
#include "ARPGDemoPlayerState.generated.h"


/**
 * 玩家状态
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
	TArray<FAbilityData> StartUpAbility;

	/**
	 * @brief 技能栏中技能
	 */
	TArray<FAbilityData> SkillBarAbilityDatas;
	
protected:
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;

	/**
	* @brief 生命值改变调用
	*/
	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	/**
	* @brief 最大生命值改变调用
	*/
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);

public:
	virtual void BeginPlay() override;

	/**
	* @brief 拿到GASC组件
	*/
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
