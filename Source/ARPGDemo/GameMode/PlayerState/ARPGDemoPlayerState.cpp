// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPGDemoPlayerState.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "ARPGDemo/Character/Player/PlayerCharacter.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/HUD/HUDAvatarFrame.h"

AARPGDemoPlayerState::AARPGDemoPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	NetUpdateFrequency = 100.0f;
	
	AbilitySetBase = CreateDefaultSubobject<UAbilitySetBase>(TEXT("AbilitySetBase"));
	SkillBarAbilityDatas.SetNum(10);
}

void AARPGDemoPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		auto AvatarFrame = UWindowManager::GetInstance()->GetWindow<UHUDAvatarFrame>(EWindowTypes::HUD_AvatarFrame);
		UHUDHealthBar* HUDHealthBar = AvatarFrame->HealthBar;
		
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
	float Health = Data.NewValue;
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		auto AvatarFrame = UWindowManager::GetInstance()->GetWindow<UHUDAvatarFrame>(EWindowTypes::HUD_AvatarFrame);
		UHUDHealthBar* HUDHealthBar = AvatarFrame->HealthBar;
		
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
