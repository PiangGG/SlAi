// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiPlayerStateWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SConstraintCanvas.h"
#include "Widgets/Notifications/SProgressBar.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPlayerStateWidget::Construct(const FArguments& InArgs)
{
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");

	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(744.0f)
		.HeightOverride(244.0f)
		[
			SNew(SOverlay)
			//状态背景图片
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&GameStyle->PlayerStateBGBrush)	
			]
			//添加进度条的CanvasPanel
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SConstraintCanvas)
				+SConstraintCanvas::Slot()
				.Anchors(FAnchors(0.0f))
				.Offset(FMargin(442.3f,90.0f,418.0f,42.0f))
				[
					SAssignNew(HPBar,SProgressBar)
					.BackgroundImage(&GameStyle->EmptyBrush)
					.FillImage(&GameStyle->HPBrush)
					.FillColorAndOpacity(FSlateColor(FLinearColor(1.0f,1.0f,1.0f,1.0f)))
					.Percent(1.0f)
				]
				+SConstraintCanvas::Slot()
				.Anchors(FAnchors(0.0f))
				.Offset(FMargin(397.5f,145.0f,317.0f,26.0f))
				[
					SAssignNew(HungerBar,SProgressBar)
					.BackgroundImage(&GameStyle->EmptyBrush)
					.FillImage(&GameStyle->HungerBrush)
					.FillColorAndOpacity(FSlateColor(FLinearColor(1.0f,1.0f,1.0f,1.0f)))
					.Percent(1.0f)
				]
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.0f,0.0f,500.0f,0.0f))
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PlayerHeadBGBrush)
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(&GameStyle->PlayerHeadBrush)
				]
			]
		]
	];
	
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiPlayerStateWidget::UpdateStateWidget(float HPValue, float HungerValue)
{
	if (HPValue>0)HPBar->SetPercent(FMath::Clamp<float>(HPValue,0.0f,1.0f));
	if (HPValue>0)HungerBar->SetPercent(FMath::Clamp<float>(HungerValue,0.0f,1.0f));	
}