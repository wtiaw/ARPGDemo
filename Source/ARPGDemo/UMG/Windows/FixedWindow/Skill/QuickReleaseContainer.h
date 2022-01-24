// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "SkillBar/SkillBar.h"
#include "QuickReleaseContainer.generated.h"

class USkillBar;
class UImage;
class USkillItem;
/**
 * @brief 技能快捷释放容器
 */
UCLASS()
class ARPGDEMO_API UQuickReleaseContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* CoolDown;
	
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

	/**
	 * @brief 在技能栏的下标
	 */
	UPROPERTY(EditAnywhere)
	int Index;

	UPROPERTY()
	USkillBar* Parent;

	UPROPERTY(BlueprintReadWrite)
	UWidgetAnimation* Active;
	
private:
	float TimeRemaining;

	float CooldownDuration;
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	UFUNCTION(BlueprintCallable)
	void SetHighLight();

	UFUNCTION(BlueprintCallable)
	void HideHighLight();

protected:
	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION()
	void OnCoolDown();
};
