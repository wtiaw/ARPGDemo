// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillItem_Visual.h"
#include "ARPGDemo/Data/AbilityData.h"
#include "ARPGDemo/UMG/Widgets/Drag/DraggableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "SkillItem.generated.h"

class UAbilityToolTip;
class UQuickReleaseContainer;
/**
 * 技能
 */
UCLASS()
class ARPGDEMO_API USkillItem : public UDraggableWidget
{
	GENERATED_BODY()

public:
	/**
	 * @brief 技能图标
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Skill Item|Visual")
	UImage* AbilityIcon;

	/**
	 * @brief 选中时的高光
	 */
	UPROPERTY(BlueprintReadOnly, Meta = (BindWidget), Category = "Skill Item|Visual")
	UImage* HighLight;

	/**
	 * @brief 高光纹理
	 */
	UPROPERTY(EditAnywhere, Category = "Skill Item|Visual")
	UMaterialInstance* HighLightTexture;

	/**
	 * @brief 快捷栏
	 */
	UPROPERTY()
	UQuickReleaseContainer* Parent = nullptr;

	/**
	 * @brief 是否拖拽成功
	 */
	bool bIsDragSucceed = false;

	/**
	 * @brief 拖拽视觉组件
	 */
	UPROPERTY(EditAnywhere, Category = "Skill Item|Visual")
	TSubclassOf<USkillItem_Visual> VisualClass;

	/**
	 * @brief 显示技能详细属性
	 */
	UPROPERTY(BlueprintReadWrite)
	UAbilityToolTip* AbilityToolTip;
	
	/**
	 * @brief 技能数据
	 */
	FAbilityData* AbilityData = &DefaultData;

	FAbilityData DefaultData = FAbilityData();

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
	
	/**
	 * @brief 材质实例
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Visual")
	UMaterialInstance* Material;
	
public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	FAbilityData* GetAbilityData();

	UFUNCTION(BlueprintCallable)
	void GetAbilityData(FAbilityData& Out);
	
	void SetAbilityData(USkillItem* SkillItem);

	void SetAbilityData(FAbilityData* InAbilityData);

	static USkillItem* GetDraggedSkillItem(UDragDropOperation* DragDropOperation);

	/**
	 * @brief 获得GAS能力句柄
	 */
	FGameplayAbilitySpec* GetGameplayAbilitySpec();

	/**
	 * @brief 设置图标材质
	 */
	void SetMaterial(UMaterialInstance* InMaterial);

	/**
	 * @brief 设置技能图标
	 */
	void SetIcon();

	/**
	 * @brief 显示选中时的高亮
	 */
	void SetHighLight() const;

	/**
	 * @brief 隐藏选中时的高亮
	 */
	void HideHighLight() const;
	
	/**
	 * @brief 授予玩家能力
	 * @param bTerminate 是否中止技能
	 */
	void GiveAbility(bool bTerminate = false);
};
