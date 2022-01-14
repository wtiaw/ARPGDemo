// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityManager.h"

#include "AbilitySystemComponent.h"
#include "ARPGDemo/Character/Player/PlayerCharacter.h"
#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "Kismet/GameplayStatics.h"

UAbilityManager* UAbilityManager::Instance = nullptr;

UAbilityManager* UAbilityManager::GetInstance()
{
	if(!Instance)
	{
		Instance = NewObject<UAbilityManager>();
		Instance->AddToRoot();
	}
	return Instance;
}

void UAbilityManager::GiveAbility(EGASAbilityInputID GASAbilityInputID, TSubclassOf<UGameplayAbility_Base> AbilityClass, int Level)
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(AARPGDemoGameMode::Instance->GetPlayerController()->GetCharacter());
	const auto AbilitySystemComponent = GetGASComponent();
	
	FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityClass,Level,static_cast<int32>(GASAbilityInputID),PlayerCharacter));

	ActiveAbility.Emplace(GASAbilityInputID,Handle);
}

void UAbilityManager::SwapAbility(EGASAbilityInputID Source, EGASAbilityInputID Target)
{
	const auto AbilitySystemComponent = GetGASComponent();
	
	auto SourceHandle = ActiveAbility.Find(Source);
	auto TargetHandle = ActiveAbility.Find(Target);
	
	if(SourceHandle && AbilitySystemComponent)
	{
		FGameplayAbilitySpec* SourceFoundSpec = AbilitySystemComponent->FindAbilitySpecFromHandle(*SourceHandle);
		
		if(TargetHandle)
		{
            FGameplayAbilitySpec* TargetFoundSpec = AbilitySystemComponent->FindAbilitySpecFromHandle(*TargetHandle);
			
            const int SpecTemp = SourceFoundSpec->InputID;
            SourceFoundSpec->InputID = TargetFoundSpec->InputID;
            TargetFoundSpec->InputID = SpecTemp;

            const auto SpecHandleTemp = SourceHandle;
			ActiveAbility[Source] = *TargetHandle;
			ActiveAbility[Target] = *SpecHandleTemp;
		}
		else
		{
			SourceFoundSpec->InputID = static_cast<int32>(Target);
			ActiveAbility.Emplace(Target,*SourceHandle);
			ActiveAbility.Remove(Source);
		}
	}
}

void UAbilityManager::ClearAbility(EGASAbilityInputID GASAbilityInputID)
{
	const auto AbilitySystemComponent = GetGASComponent();

	AbilitySystemComponent->ClearAbility(*ActiveAbility.Find(GASAbilityInputID));
	ActiveAbility.Remove(GASAbilityInputID);
}

UAbilitySystemComponent* UAbilityManager::GetGASComponent() const
{
	const auto PlayerCharacter = Cast<APlayerCharacter>(AARPGDemoGameMode::Instance->GetPlayerController()->GetCharacter());
	if(!PlayerCharacter)
		return nullptr;

	const auto AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if(!AbilitySystemComponent)
		return nullptr;
	
	return AbilitySystemComponent;
}

