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

	UPROPERTY(BlueprintReadWrite)
	UAbilityToolTip* AbilityToolTip;

protected:
	/**
	 * @brief 技能数据
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Data")
	FAbilityData AbilityData;

	/**
	 * @brief 材质实例
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Skill Item|Visual")
	UMaterialInstance* Material;
	
private:
	FGameplayAbilitySpecHandle GameplayAbilitySpecHandle;
	
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

	UFUNCTION(BlueprintCallable)
	FAbilityData GetAbilityData();

	void SetAbilityData(USkillItem* SkillItem);

	void SetAbilityData(FAbilityData InAbilityData);

	static USkillItem* GetDraggedSkillItem(UDragDropOperation* DragDropOperation);

	void SetHandle(FGameplayAbilitySpecHandle Handle);
	
	FGameplayAbilitySpecHandle GetHandle();

	void SetMaterial(UMaterialInstance* InMaterial);

	void SetIcon();

	void SetHighLight() const;

	void HideHighLight() const;

private:
	void GiveAbility();
	
	void LevelUp();
    
	bool CheckLevelUp();
};
