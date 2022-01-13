// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibraryWidget.h"

UWidget* UFunctionLibraryWidget::GetHoveredWidget(UPanelWidget* UIParent, FVector2D Position)
{
	const auto Count = UIParent->GetChildrenCount();
	for (size_t i = 0; i < Count; ++i)
	// for (auto i = Count - 1; i > -1; --i)
	{
		const auto Child = UIParent->GetChildAt(i);
		const auto ChildGeometry = Child->GetPaintSpaceGeometry();
		//只有Widget是显示的情况下才获取画布
		if (Child->GetVisibility() == ESlateVisibility::Visible ||
			Child->GetVisibility() == ESlateVisibility::SelfHitTestInvisible ||
			Child->GetVisibility() == ESlateVisibility::HitTestInvisible)
		{
			const auto Hovered = ChildGeometry.GetRenderBoundingRect().ContainsPoint(Position);
			if (Hovered)
				return Child;
		}
	}
	return nullptr;
}

UWidget* UFunctionLibraryWidget::GetMouseHoveredWidget(UPanelWidget* UIParent)
{
	const auto Count = UIParent->GetChildrenCount();
	for (size_t i = 0; i < Count; ++i)
	{
		const auto Child = UIParent->GetChildAt(i);
		if (Child->GetVisibility() == ESlateVisibility::Visible ||
			Child->GetVisibility() == ESlateVisibility::SelfHitTestInvisible ||
			Child->GetVisibility() == ESlateVisibility::HitTestInvisible)
		{
			if (Child->IsHovered())
				return Child;
		}
	}
	return nullptr;
}
