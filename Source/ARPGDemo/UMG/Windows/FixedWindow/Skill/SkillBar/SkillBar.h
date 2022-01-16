// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "ARPGDemo/UMG/Windows/FixedWindow/Skill/QuickReleaseContainer.h"
#include "Components/HorizontalBox.h"
#include "SkillBar.generated.h"

struct FGameplayTag;
/**
 * @brief 快捷技能栏
 */
UCLASS()
class ARPGDEMO_API USkillBar : public UBaseWindow
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UHorizontalBox* EffectedAbilityBar;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UHorizontalBox* CoolDownAbilityBar;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UHorizontalBox* QuickReleaseBar;
	
public:
	UFUNCTION(BlueprintCallable)
	UQuickReleaseContainer* GetQuickReleaseContainerByIndex(int Index);

	UFUNCTION(BlueprintCallable)
	UQuickReleaseContainer* GetQuickReleaseContainerByGASAbilityInputID(EGASAbilityInputID GASAbilityInputID);

	UFUNCTION(BlueprintCallable)
	TArray<UQuickReleaseContainer*> GetQuickReleaseContainersByTag(FGameplayTag Tag);
};
