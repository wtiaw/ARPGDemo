// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ARPGDemo/GamePlayAbilitySystem/GameplayAbility/GA/GameplayAbility_Base.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "SkillItem.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API USkillItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UImage* AbilityIcon;
	
protected:
	/**
	 * @brief 技能数据
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FAbilityData AbilityData;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayAbility_Base> Ability;

public:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	UFUNCTION(BlueprintCallable)
	FAbilityData GetAbilityData();

	void SetAbilityData(USkillItem* SkillItem);

	void SetAbilityData(FAbilityData InAbilityData);

	static USkillItem* GetDraggedSkillItem(UDragDropOperation* DragDropOperation);

	void SetIcon();
};
