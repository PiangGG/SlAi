// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "UI/Widget/Package/SSlAiContainerInputWidget.h"
#include "UI/Widget/Package/SSlAiContainerNormalWidget.h"
#include "UI/Widget/Package/SSlAiContainerOutputWidget.h"
#include "UI/Widget/Package/SSlAiContainerShortcutWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerBaseWidget::Construct(const FArguments& InArgs)
{
	//获取style
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	//获取工作号
	workIndex = InArgs._workIndex;

	IsHover =false;
	ChildSlot
	[
		// Populate the widget
		SAssignNew(ContainerBorder,SBorder)
		.BorderImage(&GameStyle->NormalContainerBrush)
		.Padding(FMargin(8.0f))
		[
			SAssignNew(ObjectImage,SBorder)
			.BorderImage(&GameStyle->EmptyBrush)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f,0.f,4.f,0.f))
			[
				SAssignNew(ObjectNumText,STextBlock)
				.Font(GameStyle->Font_16)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
TSharedPtr<SSlAiContainerBaseWidget> SSlAiContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int workId)
{
	TSharedPtr<SSlAiContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer,SSlAiContainerOutputWidget).workIndex(workId);
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer,SSlAiContainerInputWidget).workIndex(workId);
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer,SSlAiContainerNormalWidget).workIndex(workId);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer,SSlAiContainerShortcutWidget).workIndex(workId);
		break;
	}
	return ResultContainer;
}

void SSlAiContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	//如果鼠标移动到上边
	if (IsHovered)
	{
		if(!IsHover)ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}else
	{
		if(IsHover)ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}
	IsHover = IsHovered;
		
}
