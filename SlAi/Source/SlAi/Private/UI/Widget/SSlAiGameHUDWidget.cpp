// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget/SSlAiGameHUDWidget.h"

#include "SlateOptMacros.h"
#include "UI/Widget/SSlAiPlayerStateWidget.h"
#include "UI/Widget/SSlAiPointerWidget.h"
#include "UI/Widget/SSlAIRayInfoWidget.h"
#include "UI/Widget/SSlAiShortcutWidget.h"
#include "Widgets/Layout/SDPIScaler.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameHUDWidget::Construct(const FArguments& InArgs)
{
	UIScaler.Bind(this,&SSlAiGameHUDWidget::GetUIScaler);
	
	ChildSlot
	[
		SNew(SDPIScaler)
		.DPIScale(UIScaler)
		[
			SNew(SOverlay)
			+SOverlay::Slot()//快捷栏
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SAssignNew(ShortcutWidget,SSlAiShortcutWidget)
			]
			+SOverlay::Slot()//射线信息
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(RayInfoWidget,SSlAiRayInfoWidget)
			]
			+SOverlay::Slot()//射线信息
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            [
            	SAssignNew(PointerWidget,SSlAiPointerWidget)
            ]
            +SOverlay::Slot()//玩家状态PlayerStateWidget
            .HAlign(HAlign_Left)
            .VAlign(VAlign_Top)
            [
				SAssignNew(PlayerStateWidget,SSlAiPlayerStateWidget)
            ]
		]
	];
	
}

float SSlAiGameHUDWidget::GetUIScaler() const
{
	return GetViewporSize().Y/1080.0f;
}

FVector2D SSlAiGameHUDWidget::GetViewporSize() const
{
	FVector2D Result(1920.0f,1080.0f);
	if (GEngine&&GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(Result);		
	}
	return Result;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
