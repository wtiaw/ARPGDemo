// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "ARPGDemo/Data/AbilitySetBase.h"
#include "GameFramework/PlayerState.h"
#include "ARPGDemoPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API AARPGDemoPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AARPGDemoPlayerState();
	
	UPROPERTY(BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	UAbilitySetBase* AbilitySetBase;

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
