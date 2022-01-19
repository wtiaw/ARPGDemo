// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/Library/AsyncTask/AsyncTaskCooldownChanged.h"
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
	/**
	* @brief 技能改变的委托
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAbilityChangedDelegate);
	
	/**
	* @brief 技能改变的事件
	*/
	UPROPERTY(BlueprintAssignable)
	FAbilityChangedDelegate AbilityChanged;

	FTimerDynamicDelegate CoolDownDelegate;
	

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	UTextBlock* CoolDown;

protected:
	UPROPERTY(BlueprintReadWrite)
	UAsyncTaskCooldownChanged* AsyncTask;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle TimerHandle;
	
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
	
private:
	float SkillTimeRemaining;

	float SkillDuration;
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	/**
	 * @brief 设置快捷键文本
	 */
	UFUNCTION(BlueprintCallable)
	void SetQuickName();

	UFUNCTION(BlueprintCallable)
	void SetHighLight();

	UFUNCTION(BlueprintCallable)
	void HideHighLight();

protected:
	UFUNCTION()
	void OnAbilityCoolDownChanged();

	UFUNCTION()
	void OnCoolDownBegin(FGameplayTag CooldownTag, float TimeRemaining, float Duration);

	UFUNCTION()
	void OnCoolDownEnd(FGameplayTag CooldownTag, float TimeRemaining, float Duration);

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION()
	void OnCoolDown();
};
