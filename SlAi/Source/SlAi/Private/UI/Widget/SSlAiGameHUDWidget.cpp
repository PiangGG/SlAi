// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Widget/SSlAiGameHUDWidget.h"

#include "SlateOptMacros.h"
#include "Common/SlAiHelper.h"
#include "UI/Widget/SSlAiChatRoomWidget.h"
#include "UI/Widget/SSlAiPlayerStateWidget.h"
#include "UI/Widget/SSlAiPointerWidget.h"
#include "UI/Widget/SSlAIRayInfoWidget.h"
#include "UI/Widget/SSlAiShortcutWidget.h"
#include "UI/Widget/Package/SSlAiPackageWidget.h"
#include "Widgets/Images/SImage.h"
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
            
            //暗黑色遮罩，放在事件界面和游戏UI中间
            +SOverlay::Slot()
            .HAlign(HAlign_Fill)
            .VAlign(VAlign_Fill)
            [
				SAssignNew(BlackShade,SBorder)
				//设置为黑色透明
				.ColorAndOpacity(TAttribute<FLinearColor>(FLinearColor(0.2f,0.2f,0.2f,0.5f)))
				//初始化不显示
				.Visibility(EVisibility::Hidden)
				[
					SNew(SImage)
				]
            ]
            +SOverlay::Slot()
            .HAlign(HAlign_Center)
            .VAlign(VAlign_Center)
            [
				SAssignNew(GameMenuWidget,SSlAiGameMenuWidget)
				.Visibility(EVisibility::Hidden)
            ]
            +SOverlay::Slot()
            .VAlign(VAlign_Bottom)
            .HAlign(HAlign_Left)
            [
				SAssignNew(ChatRoomWidget,SSlAiChatRoomWidget)
				.Visibility(EVisibility::Hidden)
            ]
            +SOverlay::Slot()
            .VAlign(VAlign_Fill)
            .HAlign(HAlign_Fill)
            [
				SAssignNew(PackageWidget,SSlAiPackageWidget)
				.Visibility(EVisibility::Hidden)
				.UIScaler(UIScaler)
            ]
		]
	];
	InitUIMap();
}

float SSlAiGameHUDWidget::GetUIScaler() const
{
	return GetViewporSize().Y/1080.0f;
}

void SSlAiGameHUDWidget::ShowGameUI(EGameUIType::Type PreUI, EGameUIType::Type NextUI)
{
	//如果前一模式是Game,说明要显示黑板
	if (PreUI==EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Visible);
	}else
	{
		//隐藏当前显示的UI
		UIMap.Find(PreUI)->Get()->SetVisibility(EVisibility::Hidden);
	}
	//如果下一模式是Game,隐藏黑板
	if (NextUI==EGameUIType::Game)
	{
		BlackShade->SetVisibility(EVisibility::Hidden);
	}else
	{
		//显示现在状态对应的UI
		UIMap.Find(NextUI)->Get()->SetVisibility(EVisibility::Visible);
	}
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

void SSlAiGameHUDWidget::InitUIMap()
{
	UIMap.Add(EGameUIType::Pause,GameMenuWidget);
	UIMap.Add(EGameUIType::Package,PackageWidget);
	UIMap.Add(EGameUIType::ChatRoom,ChatRoomWidget);
	UIMap.Add(EGameUIType::Lose,GameMenuWidget);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
