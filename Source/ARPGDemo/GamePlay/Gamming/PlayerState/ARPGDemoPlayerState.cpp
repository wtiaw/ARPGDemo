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

void AARPGDemoPlayerState::LevelChanged(const FOnAttributeChangeData& Data)
{
	int Level = Data.NewValue;
	FString SLevel = FString::FromInt(Level);
	
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	if (PlayerCharacter)
	{
		auto AvatarFrame = UWindowManager::GetInstance()->GetWindow<UHUDAvatarFrame>(EWindowTypes::HUD_AvatarFrame);
		
		if (AvatarFrame)
		{
			AvatarFrame->Level->SetText(FText::FromString(SLevel));
		}
	}
}

void AARPGDemoPlayerState::XPChanged(const FOnAttributeChangeData& Data)
{
}

void AARPGDemoPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AbilitySetBase->GetHealthAttribute()).AddUObject(this, &AARPGDemoPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AbilitySetBase->GetMaxHealthAttribute()).AddUObject(this, &AARPGDemoPlayerState::MaxHealthChanged);
		LevelChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AbilitySetBase->GetLevelAttribute()).AddUObject(this, &AARPGDemoPlayerState::LevelChanged);
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

float AARPGDemoPlayerState::GetLevel() const
{
	return AbilitySetBase->GetLevel();
}

float AARPGDemoPlayerState::GetMaxLevel() const
{
	return AbilitySetBase->GetMaxLevel();
}

float AARPGDemoPlayerState::GetXP() const
{
	return AbilitySetBase->GetXP();
}

float AARPGDemoPlayerState::GetMaxXP() const
{
	return AbilitySetBase->GetMaxXP();
}

bool AARPGDemoPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}
