// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuItemWidget.h"
#include "SlateOptMacros.h"	
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "UI/Widget/SSlAiMenuWidget.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuItemWidget::Construct(const FArguments& InArgs)
{
	//获取style
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	
	OnClicked = InArgs._OnClicked;
	ItemType = InArgs._ItemType.Get();
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(500.0f)
		.HeightOverride(100.0f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
				.ColorAndOpacity(this,&SSlAiMenuItemWidget::GetTintColor)
			]
			+SOverlay::Slot()
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Center)
			[
				SNew(STextBlock)
				.Text(InArgs._ItemText)
				.Font(MenuStyle->Font_60)
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SSlAiMenuItemWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsMouseButtonDow=true;
	return FReply::Handled();
}

FReply SSlAiMenuItemWidget::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (IsMouseButtonDow)
	{
		IsMouseButtonDow=false;
		OnClicked.ExecuteIfBound(ItemType);
	}
	return FReply::Handled();
}

void SSlAiMenuItemWidget::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	IsMouseButtonDow=false;
}

FSlateColor SSlAiMenuItemWidget::GetTintColor()const
{
	if (IsMouseButtonDow) return FLinearColor(1.0f,0.1f,0.1,0.5);
	return FLinearColor(1.0f,1.0f,1.0f,1.0f);
}
