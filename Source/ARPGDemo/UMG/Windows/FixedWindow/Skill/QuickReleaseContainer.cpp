// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickReleaseContainer.h"

void UQuickReleaseContainer::SetQuickName()
{
	QuickKey->SetText(FText::FromString(QuickKeyName));
}
