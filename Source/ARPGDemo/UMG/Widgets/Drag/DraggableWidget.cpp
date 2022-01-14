// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableWidget.h"

#include "DragOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

FReply UDraggableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	this->DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UDraggableWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	bDragging = true;

	if (DragVisualWidgetClass != nullptr && DragOperationClass != nullptr)
	{
		const auto DragOperation = Cast<UDragOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(DragOperationClass));
		DragOperation->DraggedWidget = this;
		DragOperation->DragOffset = this->DragOffset;
		DragOperation->Pivot = EDragPivot::MouseDown;

		OutOperation = DragOperation;
	}
}

void UDraggableWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
    
    if (bDragging)
    {
    	bDragging = false;
    }
}
