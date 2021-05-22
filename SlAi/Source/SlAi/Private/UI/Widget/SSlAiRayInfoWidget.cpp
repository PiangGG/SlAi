// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiRayInfoWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiRayInfoWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(400.0f)
		.HeightOverride(100.f)
		[
			SNew(SBorder)
			.BorderImage(&GameStyle->RayInfoBursh)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(RayInfoTextBlock,STextBlock)
				.Font(GameStyle->Font_Outline_50)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiRayInfoWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//第一帧初始化
	if(!IsInitRayInfoEvent)
	{
		RegisterRayInfoEvent.ExecuteIfBound(RayInfoTextBlock);
		IsInitRayInfoEvent=true;
	}
}
