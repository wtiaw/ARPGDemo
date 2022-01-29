// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDHealthBar.h"
#include "ARPGDemo/GamePlay/Gamming/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/GamePlay/Gamming/PlayerState/ARPGDemoPlayerState.h"



void UHUDHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	Material = Fill->GetDynamicMaterial();

	HealthChanged();
}

void UHUDHealthBar::HealthChanged()
{
	FText OutText;
	float OutPercent;
	
	GetHealthText(OutText,OutPercent);

	Material->SetScalarParameterValue(FName(TEXT("percentage")),OutPercent);
	Health->SetText(OutText);
}

void UHUDHealthBar::GetHealthText(FText& OutText,float& OutPercent)
{
	const auto PS = AARPGDemoGameMode::Instance->GetPlayerController()->GetPlayerState<AARPGDemoPlayerState>();

	const float CurrentHealth = PS->GetHealth();
	const float MaxHealth = PS->GetMaxHealth();

	const FString Text = FString::Printf(TEXT("%.0f/%.0f"), CurrentHealth, MaxHealth);

	OutText = FText::FromString(Text);
	OutPercent = CurrentHealth / MaxHealth;
}
