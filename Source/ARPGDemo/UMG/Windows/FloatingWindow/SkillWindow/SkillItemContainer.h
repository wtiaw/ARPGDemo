// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Widgets/Drag/Skill/SkillItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SkillItemContainer.generated.h"

class UDataTable;
/**
 * 
 */
UCLASS()
class ARPGDEMO_API USkillItemContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief 技能数据表
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Data")
	UDataTable* AbilityDataTable;

	/**
	 * @brief 技能数据表的行数
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Data")
	FName AbilityName;

	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	USkillItem* SkillItem;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Level;

	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_LevelUp;

	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_LevelDown;

private:
	FAbilityData* AbilityData;

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	void SetAbilityData();

	void SetLevelText();

	/**
	 * @brief 提升技能等级
	 */
	UFUNCTION(BlueprintCallable)
	void LevelUp();

	/**
	 * @brief 降低技能等级
	 */
	UFUNCTION(BlueprintCallable)
	void LevelDown();

	/**
	 * @brief 检查是否可以提升技能等级
	 * @return 是否可以升级
	 */
	bool CheckLevelUp();

	/**
	 * @brief 检查是否可以提升技能等级
	 * @return 是否可以升级
	 */
	bool CheckLevelDown();

	void CheckButton();
};
