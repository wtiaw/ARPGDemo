// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/UMG/Widgets/Drag/Skill/SkillItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "SkillItemContainer.generated.h"

class UCustomSaveGame;
class UDataTable;

/**
 * @brief 技能容器
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
	 * @brief 技能数据表的行名
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Data")
	FName AbilityName;

	/**
	 * @brief 技能
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget))
	USkillItem* SkillItem;

	/**
	 * @brief 技能等级
	 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* Level;

	/**
	 * @brief 技能升级按钮
	 */
	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_LevelUp;

	/**
	 * @brief 技能降级按钮
	 */
	UPROPERTY(Meta = (BindWidget))
	UButton* Btn_LevelDown;

private:
	/**
	 * @brief 技能数据
	 */
	FAbilityData* AbilityData;

	/**
	 * @brief 存档实例
	 */
	UPROPERTY()
	UCustomSaveGame* Save;
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	/**
	 * @brief 从技能数据表中获得技能数据
	 */
	void SetAbilityData();

	/**
	 * @brief 设置技能等级文本
	 */
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

	/**
	 * @brief 设置按钮
	 */
	void CheckButton();
};
