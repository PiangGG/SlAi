// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SDPIScaler.h"
//#include "SButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//绑定缩放规则方法
	UIScaler.Bind(this,&SSlAiMenuHUDWidget::GetUIScaler);
	if (MenuStyle)
	{
		UE_LOG(LogTemp,Warning,TEXT("MenuStyle"));
		if (&MenuStyle->MenuHUDBackgroundBrush)
		{
			UE_LOG(LogTemp,Warning,TEXT("&MenuStyle->MenuHUDBackgroundBrush"));
		}
	}
	ChildSlot
        [
            // Populate the widget

            SNew(SDPIScaler)
            .DPIScale(UIScaler)
            [
	            SNew(SOverlay)//界面适配
	            +SOverlay::Slot()//添加插槽可以添加子物体
	            .HAlign(HAlign_Fill)
	            .VAlign(VAlign_Fill)
	            //.Padding(FMargin(30.f))边框
	            [
	                SNew(SImage)
	                .Image(&MenuStyle->MenuHUDBackgroundBrush)
	            ]
	            +SOverlay::Slot()
	            .HAlign(HAlign_Center)
	            .VAlign(VAlign_Center)
	            [
	                SNew(SImage)
	                .Image(&MenuStyle->MenuBackgroundBrush)
	            ]
			]
			//SNew(SButton).Text(FName("123"))
		];
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

float SSlAiMenuHUDWidget::GetUIScaler() const
{
	return GetViewportSize().Y/1080.0f;
}

FVector2D SSlAiMenuHUDWidget::GetViewportSize() const
{
	FVector2D Result(1920,1080);
	if (GEngine&&GEngine->GameViewport)
		GEngine->GameViewport->GetViewportSize(Result);
	return Result;
}

