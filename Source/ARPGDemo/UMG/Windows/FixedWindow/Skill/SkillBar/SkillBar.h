// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ARPGDemo/UMG/Windows/BaseWindow/BaseWindow.h"
#include "Components/HorizontalBox.h"
#include "SkillBar.generated.h"

class UQuickReleaseContainer;
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

	UPROPERTY(EditAnywhere)
	FGameplayTag CoolDownTag;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer CoolDownTags;
public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable)
	UQuickReleaseContainer* GetQuickReleaseContainerByIndex(int Index);
};
