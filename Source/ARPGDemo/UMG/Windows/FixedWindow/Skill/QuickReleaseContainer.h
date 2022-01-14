// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillItem.h"
#include "ARPGDemo/Data/Enum/EGASAbilityInputID.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "QuickReleaseContainer.generated.h"

/**
 * @brief 技能快捷释放容器
 */
UCLASS()
class ARPGDEMO_API UQuickReleaseContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief 技能改变的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityChangedDelegate);

	/**
	* @brief 技能改变的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FAbilityChangedDelegate AbilityChanged;
	
public:
	/**
	 * @brief 快捷键名称
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString QuickKeyName;

	/**
	 * @brief 动作名称
	 */
	UPROPERTY(EditAnywhere)
	EGASAbilityInputID GASAbilityInputID;

	/**
	 * @brief 快捷键文本显示
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* QuickKey;

	/**
	 * @brief 技能Item
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	USkillItem* SkillItem;

	/**
	 * @brief 技能框
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UImage* Background;

	/**
	 * @brief 快捷键框
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UImage* QuickKeyBackground;
	
public:
	virtual void NativeConstruct() override;
	
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	/**
	 * @brief 设置快捷键文本
	 */
	UFUNCTION(BlueprintCallable)
	void SetQuickName();

	void SetHighLight();

	void HideHighLight();
};
