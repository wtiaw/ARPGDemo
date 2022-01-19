// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerState.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "ARPGDemo/Character/Player/PlayerCharacter.h"

AARPGDemoPlayerState::AARPGDemoPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySetBase = CreateDefaultSubobject<UAbilitySetBase>(TEXT("AbilitySetBase"));

	AbilityHandles.SetNum(10);
}

void AARPGDemoPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UHUDHealthBar* HUDHealthBar = PlayerCharacter->HUDHealthBar;
		if (HUDHealthBar)
		{
			HUDHealthBar->HealthChanged();
		}
	}
	
	// if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	// {
	// 	if (Hero)
	// 	{
	// 		Hero->Die();
	// 	}
	// }
}

void AARPGDemoPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		UHUDHealthBar* HUDHealthBar = PlayerCharacter->HUDHealthBar;
		if (HUDHealthBar)
		{
			HUDHealthBar->HealthChanged();
		}
	}
}

void AARPGDemoPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AbilitySetBase->GetHealthAttribute()).AddUObject(this, &AARPGDemoPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AbilitySetBase->GetMaxHealthAttribute()).AddUObject(this, &AARPGDemoPlayerState::MaxHealthChanged);
	}
}

UAbilitySystemComponent* AARPGDemoPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAbilitySetBase* AARPGDemoPlayerState::GetAttributeSetBase() const
{
	return AbilitySetBase;
}

float AARPGDemoPlayerState::GetHealth() const
{
	return AbilitySetBase->GetHealth();
}

float AARPGDemoPlayerState::GetMaxHealth() const
{
	return AbilitySetBase->GetMaxHealth();
}

bool AARPGDemoPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}
