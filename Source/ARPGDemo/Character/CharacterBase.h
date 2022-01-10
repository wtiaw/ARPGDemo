// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class ARPGDEMO_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
public:
	ACharacterBase();
	
protected:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
