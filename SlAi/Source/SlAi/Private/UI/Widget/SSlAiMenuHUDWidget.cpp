// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"
//#include "SButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	//获取编辑器的MenuStyle
	MenuStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

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
			SNew(SImage)
			.Image(&MenuStyle->MenuHUDBackgroundBrush)
			//SNew(SButton).Text(FName("123"))
		];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
