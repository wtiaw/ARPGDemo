// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ARPGDemo/Data/AbilitySetBase.h"
#include "CharacterBase.generated.h"

UCLASS()
class ARPGDEMO_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UAbilitySetBase> AbilitySetBase;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
	UPROPERTY(EditAnywhere, Category = Abilities)
	int32 CharacterLevel;

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	
public:
	ACharacterBase();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void AddStartupGameplayAbilities();
};
