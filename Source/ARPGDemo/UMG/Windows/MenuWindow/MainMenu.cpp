// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
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
}

void UMainMenu::OnClose()
{
	UGameplayStatics::SetGamePaused(this,false);
	
	if(WindowClose.IsBound())
 	{
 		WindowClose.Broadcast();
 	}

	if(AARPGDemoGameMode::Instance->GetPlayerController())
	{
		WindowOpen.RemoveDynamic(AARPGDemoGameMode::Instance->GetPlayerController(),&AARPGDemoPlayerController::OnShowMouseCursor);
		WindowClose.RemoveDynamic(AARPGDemoGameMode::Instance->GetPlayerController(),&AARPGDemoPlayerController::OnHideMouseCursor);
	}
}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	SetFocus();
	
	Btn_Quit->OnClicked.AddDynamic(this,&UMainMenu::Quit);
	
	WindowOpen.AddDynamic(AARPGDemoGameMode::Instance->GetPlayerController(),&AARPGDemoPlayerController::OnShowMouseCursor);
	WindowClose.AddDynamic(AARPGDemoGameMode::Instance->GetPlayerController(),&AARPGDemoPlayerController::OnHideMouseCursor);

	OnOpen();
}

void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();

	OnClose();
}

FReply UMainMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if(InKeyEvent.GetKey() == EKeys::Escape)
    {
        UGameplayStatics::SetGamePaused(this,false);
        
        RemoveFromParent();
    }
        
    return FReply::Handled();
}

void UMainMenu::Quit()
{
	UKismetSystemLibrary::QuitGame(this,AARPGDemoGameMode::Instance->GetPlayerController(),EQuitPreference::Quit,false);
}
