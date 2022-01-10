// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Base.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameplayAbility_Base::ShowCoolDownTime()
{
	UE_LOG(LogTemp,Warning,TEXT("Start Counting"));
	UE_LOG(LogTemp,Warning,TEXT("%f"),GetCooldownTimeRemaining());

	if(GetCooldownTimeRemaining() == 0)
	{
		UKismetSystemLibrary::K2_ClearAndInvalidateTimerHandle(this,CoolDownTimerHandle);
	}
}

void UGameplayAbility_Base::CoolDown()
{
	const float WorldDeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	// CoolDownTimerHandle = UKismetSystemLibrary::K2_SetTimer(
	// 	this,TEXT("ShowCoolDownTime"), WorldDeltaSeconds, true);

	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.SetTimer(CoolDownTimerHandle,this,&UGameplayAbility_Base::ShowCoolDownTime,WorldDeltaSeconds,true);
	
	UE_LOG(LogTemp,Warning,TEXT("Start Cool Down"));
}
