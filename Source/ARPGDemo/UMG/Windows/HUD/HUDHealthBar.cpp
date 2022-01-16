// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDHealthBar.h"
#include "ARPGDemo/GameMode/ARPGDemoGameMode.h"
#include "ARPGDemo/GameMode/PlayerState/ARPGDemoPlayerState.h"


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
	const auto Character = AARPGDemoGameMode::Instance->GetPlayerController()->GetPlayerState<AARPGDemoPlayerState>();

	const float CurrentHealth = Character->GetHealth();
	const float MaxHealth = Character->GetMaxHealth();

	const FString Text = FString::Printf(TEXT("%.0f/%.0f"), CurrentHealth, MaxHealth);

	OutText = FText::FromString(Text);
	OutPercent = CurrentHealth / MaxHealth;
}
