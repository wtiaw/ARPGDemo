// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DraggableWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARPGDEMO_API UDraggableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	* @brief 是否正在拖拽
	*/
	UPROPERTY(BlueprintReadOnly)
	bool bDragging;

	/**
	* @brief 鼠标点击组件时的位置偏移
	*/
	FVector2D DragOffset;

protected:
	TSubclassOf<UUserWidget> DragVisualWidgetClass;
	TSubclassOf<UDragDropOperation> DragOperationClass;

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
