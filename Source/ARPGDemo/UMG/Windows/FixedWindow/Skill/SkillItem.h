// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPGDemo/Data/AbilityData.h"
#include "ARPGDemo/UMG/Widgets/Drag/DraggableWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "SkillItem.generated.h"

class UQuickReleaseContainer;
/**
 * 
 */
UCLASS()
class ARPGDEMO_API USkillItem : public UDraggableWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UImage* AbilityIcon;

	UPROPERTY()
	UQuickReleaseContainer* Parent = nullptr;

	bool bIsDragSucceed = false;
protected:
	/**
	 * @brief 技能数据
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FAbilityData AbilityData;
	
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

	void SetIcon();

	void SetHighLight() const;

	void HideHighLight() const;
};
