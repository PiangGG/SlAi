// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

	ChildSlot
	[
		// Populate the widget
		SAssignNew(RootSizeBox,SBox)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.0f,50.0f,0.0f,0.0f))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuBackgroundBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.0f,25.0f,0.0f,0.0f))
			[
				SNew(SImage)
				.Image(&MenuStyle->LeftIconBruch)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.0f,25.0f,0.0f,0.0f))
			[
				SNew(SImage)
				.Image(&MenuStyle->RightIconBruch)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.WidthOverride(400.0f)
				.HeightOverride(100.0f)
				[
					SNew(SBorder)
					.BorderImage(&MenuStyle->TitleBorderBrush)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
					SAssignNew(TitleText, STextBlock)//标题
					//.Font(SlAiStyle::Get().GetFontStyle("MenuItemFont"))
					//.Text(FText::FromString("I am 12"))
					.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))//文字本地化
					]
				]
			]
		]
	];
	RootSizeBox->SetWidthOverride(600.0f);
	RootSizeBox->SetHeightOverride(510.f);
	if (&MenuStyle->SlateFontInfo&&TitleText)
	{
		TitleText->SetFont(FSlateFontInfo(MenuStyle->SlateFontInfo));
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
