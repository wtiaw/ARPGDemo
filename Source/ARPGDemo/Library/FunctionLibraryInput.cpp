// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraryInput.h"
#include "ARPGDemo/GamePlay/Gamming/PlayerController/ControllerRegister.h"
#include "GameFramework/InputSettings.h"

TArray<FKey> UFunctionLibraryInput::GetActionKey(FName InActionName)
{
	TArray<FKey> Keys;
	TArray<FInputActionKeyMapping> Actions;
	
	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	Settings->GetActionMappingByName(InActionName, Actions);

	for (auto i : Actions)
	{
		Keys.Emplace(i.Key);
	}

	return Keys;
}

FName UFunctionLibraryInput::GetActionName(FKey InActionKey)
{
	FName ActionName;
	TArray<FInputActionKeyMapping> Actions;

	UInputSettings* Settings = const_cast<UInputSettings*>(GetDefault<UInputSettings>());
	TArray<FInputActionKeyMapping> ActionMappings = Settings->GetActionMappings();

	for (auto i : ActionMappings)
	{
		if (i.Key == InActionKey)
		{
			ActionName = i.ActionName;
			break;
		}
	}

	return ActionName;
}

void UFunctionLibraryInput::ExecuteActionByActionName(FName InActionName)
{
	const auto Register = UControllerRegister::GetInstance();
	
	const FString ActionName = InActionName.ToString();
	if (ActionName == TEXT("OpenSkillWindow"))
	{
		if (Register->OpenSkillWindowDelegate.IsBound())
			Register->OpenSkillWindowDelegate.Broadcast();
	}
	else if (ActionName == TEXT("OpenBackpackWindow"))
	{
		if (Register->OpenBackpackWindowDelegate.IsBound())
			Register->OpenBackpackWindowDelegate.Broadcast();
	}
	else if (ActionName == TEXT("OpenPropertyWindow"))
	{
		if (Register->OpenPropertyWindowDelegate.IsBound())
			Register->OpenPropertyWindowDelegate.Broadcast();
	}
	else if (ActionName == TEXT("OpenMainMenu"))
	{
		if (Register->OpenMenuDelegate.IsBound())
			Register->OpenMenuDelegate.Broadcast();
	}
	else if (ActionName == TEXT("ShowMouse"))
	{
		if (Register->HideMouseCursor.IsBound())
			Register->HideMouseCursor.Broadcast();
	}
}

void UFunctionLibraryInput::ExecuteActionByKey(FKey InActionKey)
{
	const FName ActionName = GetActionName(InActionKey);

	ExecuteActionByActionName(ActionName);
}
