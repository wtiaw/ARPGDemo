// Fill out your copyright notice in the Description page of Project Settings.


#include "SettingWindow.h"

#include "ARPGDemo/UMG/Widgets/Menu/InputSetting.h"
#include "ARPGDemo/UMG/Windows/WindowManager.h"
#include "GameFramework/InputSettings.h"

void USettingWindow::NativeConstruct()
{
	Super::NativeConstruct();

	for(int i = 0 ;i < InputSettingBox->GetChildrenCount();i++)
	{
		auto Widget = Cast<UInputSetting>(InputSettingBox->GetChildAt(i));
		Widget->Parent = this;
		Widget->Index = i;
		InputKeys.Emplace(Widget->Key->Text.ToString());
	}
}

void USettingWindow::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(InputKey != EKeys::Invalid)
	{
		UInputSettings* Settings;
		Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());

		if(InputSettingWidget)
		{
			TArray<FInputActionKeyMapping> Mapping;
			Settings->GetActionMappingByName(FName(*InputSettingWidget->QuickKeyName),Mapping);

			Settings->RemoveActionMapping(Mapping[0]);
			auto NewMapping = FInputActionKeyMapping(FName(*InputSettingWidget->QuickKeyName),InputKey);
			Settings->AddActionMapping(NewMapping);
			Settings->ForceRebuildKeymaps();
			
			Settings->SaveKeyMappings();

			bSetInputKey = false;
			InputKey = EKeys::Invalid;
			InputSettingWidget->ShowKey();
			
			// InputKeys[InputSettingWidget->Index] = InputKey.GetDisplayName().ToString();
			// CheckInput(InputKey.GetDisplayName());
			//
			// if(Conflict.Num() > 0)
			// {
			// 	Indexs Indexs = Conflict[InputKey.GetDisplayName()];
			// 	for(auto i : Indexs.Index)
			// 	{
			// 		Cast<UInputSetting>(InputSettingBox->GetChildAt(i))->SetWarningText();
			// 	}
			// }
			// else
			// {
			// 	InputSettingWidget->SetNormalText();
			// 	Cast<UInputSetting>(InputSettingBox->GetChildAt(Index))->SetNormalText();
			// }
		}
	}
}

FReply USettingWindow::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if(bSetInputKey)
	{
		InputKey = InKeyEvent.GetKey();
	}
	else
	{
		if(InKeyEvent.GetKey() == EKeys::Escape)
		{
			RemoveFromParent();

			const auto Widget = UWindowManager::GetInstance()->GetWindow(EWindowTypes::Menu_MainWindow);
			Widget->SetVisibility(ESlateVisibility::Visible);
			Widget->SetFocus();
		}
	}

	return FReply::Handled();
}

// void USettingWindow::CheckInput(FText BeChecked)
// {
// 	Indexs Indexs;
// 	for (int i = 0; i < InputKeys.Num(); i++)
// 	{
// 		if (InputKeys[i] == BeChecked.ToString())
// 		{
// 			Indexs.Index.Emplace(i);
// 		}
// 	}
// 	if(Indexs.Index.Num()>0)
// 	{
// 		Conflict.Emplace(BeChecked,Indexs);
// 	}
// }
