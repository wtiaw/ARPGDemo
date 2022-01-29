// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ARPGDemo/GamePlay/Gamming/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/GamePlay/Gamming/PlayerController/ControllerRegister.h"
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

	if(UControllerRegister::GetInstance())
	{
		WindowOpen.RemoveDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnShowMouseCursor);
		WindowClose.RemoveDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnHideMouseCursor);
	}
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	Btn_Quit->OnClicked.AddDynamic(this,&UMainMenu::Quit);
	
	WindowOpen.AddDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnShowMouseCursor);
	WindowClose.AddDynamic(UControllerRegister::GetInstance(),&UControllerRegister::OnHideMouseCursor);

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
