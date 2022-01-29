// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWindow.h"

#include "ARPGDemo/GamePlay/Gamming/PlayerController/ControllerRegister.h"
#include "ARPGDemo/Library/FunctionLibraryInput.h"
#include "ARPGDemo/Library/FunctionLibraryWidget.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "ARPGDemo/UMG/Windows/MainWindows/FloatingMainWindow.h"
#include "ARPGDemo/UMG/Windows/MainWindows/MainWindow.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/CanvasPanel.h"

UBaseWindow::UBaseWindow(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UBaseWindow::RegisterWindow(EWindowTypes InWindowType, UBaseWindow* Window)
{
	UWindowManager::GetInstance()->RegisterWindow(InWindowType,Window);
}

void UBaseWindow::NativeConstruct()
{
	Super::NativeConstruct();
	
	RegisterWindow(WindowType,this);
}

FReply UBaseWindow::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	UFunctionLibraryInput::ExecuteActionByKey(InKeyEvent.GetKey());

	return FReply::Handled();
}

FReply UBaseWindow::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	const UFloatingMainWindow* FloatingMainWindow = UWindowManager::GetInstance()->GetWindow<UFloatingMainWindow>(EWindowTypes::Floating_MainWindow);
	const UMainWindow* MainWindow = UWindowManager::GetInstance()->GetWindow<UMainWindow>(EWindowTypes::Fixed_MainWindow);
	
	if(!UFunctionLibraryWidget::GetMouseHoveredWidget(FloatingMainWindow->Canvas) && !UFunctionLibraryWidget::GetMouseHoveredWidget(MainWindow->MainPanel))
	{
		const auto Register = UControllerRegister::GetInstance();
		if(Register->HideMouseCursor.IsBound())
		{
			Register->HideMouseCursor.Broadcast();
		}
	}

	return FReply::Handled();
}

EWindowTypes UBaseWindow::GetWindowType() const
{
	return WindowType;
}
