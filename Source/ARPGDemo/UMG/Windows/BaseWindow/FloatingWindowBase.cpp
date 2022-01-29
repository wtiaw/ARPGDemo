// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingWindowBase.h"

#include "ARPGDemo/GamePlay/Gamming/PlayerController/ControllerRegister.h"
#include "ARPGDemo/Library/FunctionLibraryInput.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

FVector2D UFloatingWindowBase::GetWindowSize() const
{
	return FVector2D(SizeBox->WidthOverride,SizeBox->HeightOverride);
}

void UFloatingWindowBase::OnOpen()
{
	if (WindowOpen.IsBound() && UWindowManager::GetInstance()->ShouldShowMouseCursor())
		WindowOpen.Broadcast();

	OnOpenOverride();
}

void UFloatingWindowBase::OnClose()
{
	if (WindowClosed.IsBound() && UWindowManager::GetInstance()->ShouldHideMouseCursor())
		WindowClosed.Broadcast();

	OnCloseOverride();
}

void UFloatingWindowBase::Close()
{
	UWindowManager::GetInstance()->CloseFloatingWindow(WindowType);
}

void UFloatingWindowBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetFocus();
	
	BtnClose->OnClicked.AddDynamic(this, &UFloatingWindowBase::OnBtnCloseClicked);
	
	WindowOpen.AddDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnShowMouseCursor);
	WindowClosed.AddDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnHideMouseCursor);
}

void UFloatingWindowBase::NativeDestruct()
{
	Super::NativeDestruct();

	BtnClose->OnClicked.RemoveDynamic(this, &UFloatingWindowBase::OnBtnCloseClicked);

	if(UControllerRegister::GetInstance())
	{
		WindowOpen.RemoveDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnShowMouseCursor);
		WindowClosed.RemoveDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnHideMouseCursor);
	}
}

FReply UFloatingWindowBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		Close();
	}
	else
	{
		UFunctionLibraryInput::ExecuteActionByKey(InKeyEvent.GetKey());
	}

	return FReply::Handled();
}

FReply UFloatingWindowBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && TitleBar->IsHovered())
	{
		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), InMouseEvent.GetScreenSpacePosition(), PixelPosition, ViewportPosition);
		LastMouseViewportPosition = ViewportPosition;

		FEventReply DetectDragReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return UWidgetBlueprintLibrary::CaptureMouse(DetectDragReturnValue, this).NativeReply;
	}

	return FReply::Handled();
}

FReply UFloatingWindowBase::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (bDragging && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bDragging = false;
		FEventReply DetectDragReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		Reply = UWidgetBlueprintLibrary::ReleaseMouseCapture(DetectDragReturnValue).NativeReply;
	}

	return Reply;
}

FReply UFloatingWindowBase::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bDragging)
	{
		FEventReply DetectDragReturnValue;

		if (!InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
		{
			bDragging = false;
			DetectDragReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			return UWidgetBlueprintLibrary::ReleaseMouseCapture(DetectDragReturnValue).NativeReply;
		}

		DetectDragReturnValue = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

		USlateBlueprintLibrary::AbsoluteToViewport(GetWorld(), InMouseEvent.GetScreenSpacePosition(), PixelPosition, ViewportPosition);
		MouseViewportPositionDelta = ViewportPosition - LastMouseViewportPosition;
		LastMouseViewportPosition = ViewportPosition;

		UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->SetPosition(UWidgetLayoutLibrary::SlotAsCanvasSlot(this)->GetPosition() + MouseViewportPositionDelta);
		
		return UWidgetBlueprintLibrary::CaptureMouse(DetectDragReturnValue, this).NativeReply;
	}

	return FReply::Handled();
}

FReply UFloatingWindowBase::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseWheel(InGeometry, InMouseEvent);
}

void UFloatingWindowBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	bDragging = true;
}

void UFloatingWindowBase::OnOpenOverride()
{
	SetFocus();
	
	if(OpenSoundCue)
	{
		UGameplayStatics::PlaySound2D(this,OpenSoundCue);
	}
}

void UFloatingWindowBase::OnCloseOverride()
{
	if(CloseSoundCue)
 	{
 		UGameplayStatics::PlaySound2D(this,CloseSoundCue);
 	}
}

void UFloatingWindowBase::OnBtnCloseClicked()
{
	Close();
}