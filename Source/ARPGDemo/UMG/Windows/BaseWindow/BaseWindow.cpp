// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWindow.h"

#include "ARPGDemo/UMG/Windows/WindowManager.h"

void UBaseWindow::RegisterWindow(EWindowTypes InWindowType, UBaseWindow* Window)
{
	UWindowManager::Instance->RegisterWindow(InWindowType,Window);
}

void UBaseWindow::NativeConstruct()
{
	Super::NativeConstruct();

	RegisterWindow(WindowType,this);
}

EWindowTypes UBaseWindow::GetWindowType() const
{
	return WindowType;
}
