// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDMouseCursor.h"

void UHUDMouseCursor::SetShowMouse()
{
	Icon->SetBrushFromTexture(ShowMouse);
}

void UHUDMouseCursor::SetHideMouse()
{
	Icon->SetBrushFromTexture(HideMouse);
}
