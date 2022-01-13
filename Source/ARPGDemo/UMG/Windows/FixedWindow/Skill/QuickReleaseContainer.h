// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillItem.h"
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
	 * @brief 快捷键名称
	 */
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	FString QuickKeyName;

	/**
	 * @brief 快捷键文本显示
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* QuickKey;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	USkillItem* SkillItem;
	
public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	/**
	 * @brief 设置快捷键文本
	 */
	UFUNCTION(BlueprintCallable)
	void SetQuickName();
};
