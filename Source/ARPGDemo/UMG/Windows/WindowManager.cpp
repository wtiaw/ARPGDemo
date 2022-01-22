// Fill out your copyright notice in the Description page of Project Settings.


#include "WindowManager.h"
#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "BaseWindow/FloatingWindowBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "MainWindows/FloatingMainWindow.h"
#include "MainWindows/MainWindow.h"


UWindowManager* UWindowManager::Instance = nullptr; 

UWindowManager::UWindowManager()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainWindowClassFinder(TEXT("/Game/ARPGDemo/Blueprints/UMG/Windows/MainWindow/WBP_MainWindow"));
	if (MainWindowClassFinder.Succeeded())
		MainWindowClass = MainWindowClassFinder.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> FloatingMainWindowClassFinder(TEXT("/Game/ARPGDemo/Blueprints/UMG/Windows/MainWindow/WBP_FloatingMainWindow"));
	if (FloatingMainWindowClassFinder.Succeeded())
		FloatingMainWindowClass = FloatingMainWindowClassFinder.Class;
}

void UWindowManager::BeginPlay()
{
	UMainWindow* MainWindow = CreateWidget<UMainWindow>(AARPGDemoGameMode::Instance->GetPlayerController(), MainWindowClass);
	MainWindow->AddToViewport();

	UFloatingMainWindow* FloatingMainWindow = CreateWidget<UFloatingMainWindow>(AARPGDemoGameMode::Instance->GetPlayerController(), FloatingMainWindowClass);
	FloatingMainWindow->AddToViewport();
}

void UWindowManager::RegisterWindow(const EWindowTypes WindowType, UBaseWindow* Window)
{
	if (WindowType == EWindowTypes::None)
	{
		UE_LOG(LogTemp, Error, TEXT("The window type of the window[%s] you want to register is null!"), *Window->GetName());
		return;
	}

	if (!Window)
	{
		UE_LOG(LogTemp, Error, TEXT("The window pointer of the window[WindowType: %s] you want to register is null!"), *StaticEnum<EWindowTypes>()->GetNameStringByValue((int64)WindowType));
		return;
	}

	WindowMap.Emplace(WindowType, Window);
}

UBaseWindow* UWindowManager::GetWindow(const EWindowTypes WindowType)
{
	UBaseWindow** ValuePointer = WindowMap.Find(WindowType);
	
	if (ValuePointer)
	{
		UBaseWindow* Window = *ValuePointer;
		if (Window)
			return Window;
	}

	return nullptr;
}

void UWindowManager::UnregisterWindow(UBaseWindow* Window)
{
	if (!Window)
		return;

	const EWindowTypes* WindowType = WindowMap.FindKey(Window);
	if (WindowType)
		WindowMap.Remove(*WindowType);
}

void UWindowManager::OpenFloatingWindow(const EWindowTypes WindowType, const FVector2D WindowPosition)
{
	UFloatingWindowBase* ExistingWindow = GetWindow<UFloatingWindowBase>(WindowType);
	if (ExistingWindow)
	{
		ExistingWindow->SetVisibility(ESlateVisibility::Visible);
		ExistingWindow->OnOpen();
		return;
	}

	TSubclassOf<UFloatingWindowBase>* FloatingWindowClass = GetWindow<UFloatingMainWindow>(EWindowTypes::Floating_MainWindow)->FloatingWindows.FindByPredicate([WindowType](const TSubclassOf<UFloatingWindowBase> Class)
	{
		UFloatingWindowBase* FloatingWindow = Class.GetDefaultObject();
		if (!FloatingWindow)
			return false;

		return FloatingWindow->GetWindowType() == WindowType;
	});

	if (FloatingWindowClass)
	{
		UFloatingWindowBase* FloatingWindow = CreateWidget<UFloatingWindowBase>(AARPGDemoGameMode::Instance->GetPlayerController(), *FloatingWindowClass);
		if (!FloatingWindow)
			return;

		if (!FloatingWindowList.Contains(FloatingWindow))
			FloatingWindowList.Emplace(FloatingWindow);

		GetWindow<UFloatingMainWindow>(EWindowTypes::Floating_MainWindow)->Canvas->AddChild(FloatingWindow);
		UWidgetLayoutLibrary::SlotAsCanvasSlot(FloatingWindow)->SetAnchors(FAnchors(.5f));
		UWidgetLayoutLibrary::SlotAsCanvasSlot(FloatingWindow)->SetPosition(WindowPosition);
		UWidgetLayoutLibrary::SlotAsCanvasSlot(FloatingWindow)->SetSize(FloatingWindow->GetWindowSize());
		UWidgetLayoutLibrary::SlotAsCanvasSlot(FloatingWindow)->SetAlignment(FVector2D(.5f));

		FloatingWindow->OnOpen();
	}
}

void UWindowManager::CloseFloatingWindow(const EWindowTypes WindowType)
{
	UFloatingWindowBase* FloatingWindow = GetWindow<UFloatingWindowBase>(WindowType);
	if (!FloatingWindow)
		return;

	if (FloatingWindowList.Contains(FloatingWindow))
	{
		FloatingWindow->SetVisibility(ESlateVisibility::Collapsed);
	}

	FloatingWindow->OnClose();
}

bool UWindowManager::ShouldHideMouseCursor()
{
	for(auto i : FloatingWindowList)
	{
		if(i && i->Visibility == ESlateVisibility::Visible)
		{
			return false;
		}
	}
	return true; 	
}

bool UWindowManager::ShouldShowMouseCursor()
{
	return FloatingWindowList.Num() == 1 ? true :false; 
}
