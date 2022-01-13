// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/GameMode/PlayerController/ControllerRegistrar.h"
#include "Kismet/GameplayStatics.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsFocusable = true;
}

void UMainMenu::OnOpen()
{
	UGameplayStatics::SetGamePaused(this,true);
	
	if(WindowOpen.IsBound())
 	{
 		WindowOpen.Broadcast();
 	}

	SetFocus();
}

void UMainMenu::OnClose()
{
	UGameplayStatics::SetGamePaused(this,false);
	
	if(WindowClose.IsBound())
 	{
 		WindowClose.Broadcast();
 	}

	if(UControllerRegistrar::GetInstance())
	{
		WindowOpen.RemoveDynamic(UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnShowMouseCursor);
		WindowClose.RemoveDynamic(UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnHideMouseCursor);
	}
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	Btn_Quit->OnClicked.AddDynamic(this,&UMainMenu::Quit);
	
	WindowOpen.AddDynamic(UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnShowMouseCursor);
	WindowClose.AddDynamic(UControllerRegistrar::GetInstance(),&UControllerRegistrar::OnHideMouseCursor);

	OnOpen();
}

void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	OnClose();
}

FReply UMainMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if(InKeyEvent.GetKey() == EKeys::Escape)
    {
        UGameplayStatics::SetGamePaused(this,false);
        
        RemoveFromParent();
    }
        
    return FReply::Handled();
}

FReply UMainMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

void UMainMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(this,AARPGDemoGameMode::Instance->GetPlayerController(),EQuitPreference::Quit,false);
}
