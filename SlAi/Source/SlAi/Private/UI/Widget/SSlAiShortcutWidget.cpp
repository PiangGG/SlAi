// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiShortcutWidget.h"
#include "SlateOptMacros.h"
#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "Data/SlAiTypes.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiShortcutWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle = &SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(900.0f)
		.HeightOverride(160.0f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SAssignNew(ShorcutInfoTextBlock,STextBlock)
				.Font(GameStyle->Font_Outline_40)
				.ColorAndOpacity(GameStyle->FontColor_White)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(0.0f,60.0f,0.0f,0.0f)
			[
				SAssignNew(GaidPanel,SUniformGridPanel)
				
			]
		]
	];
	//设置没有初始化容器
	IsInitializeContainer =false;
}

void SSlAiShortcutWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	if (!IsInitializeContainer)
	{
		IsInitializeContainer=true;
		InitializeContainer();
	}
}

void SSlAiShortcutWidget::InitializeContainer()
{
	TArray<TSharedPtr<ShortcutContainer>> ContainerList;
	
	for (int i=0;i<9;++i)
	{
		SlAiHelper::Debug(FString::FromInt(i));
		//创建容器
		TSharedPtr<SBorder> ContainerBorder;
		TSharedPtr<SBorder> ObjectImage;
		TSharedPtr<STextBlock>ObjectNumText;

		SAssignNew(ContainerBorder,SBorder)
		.Padding(10.0f)
		//.BorderImage(&GameStyle->NormalContainerBrush)
		[
			SAssignNew(ObjectImage,SBorder)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			//.BorderImage(&GameStyle->EmptyBrush)
			.Padding(FMargin(0.0f,0.0f,5.0f,0.0f))
			[
				SAssignNew(ObjectNumText,STextBlock)
				.Font(GameStyle->Font_Outline_20)
				.ColorAndOpacity(GameStyle->FontColor_Black)
				//.Text(FText::FromString("1211111"))
			]
		];
		GaidPanel->AddSlot(i,0)
		[
			ContainerBorder->AsShared()
		];
		//实例化一个容器结构体
		TSharedPtr<ShortcutContainer> Container = MakeShareable(new ShortcutContainer
			(ContainerBorder,ObjectImage,ObjectNumText,&GameStyle->NormalContainerBrush,
				&GameStyle->ChoosedContainerBrush,&SlAiDataHandle::Get()->ObjectBrushList));
		if (i==0)Container->SetChoosed(true);
		ContainerList.Add(Container);
	}
	//将实例化的结构体注册进PlayerState的容器数组
	RegisterShortCutContainer.ExecuteIfBound(&ContainerList,ShorcutInfoTextBlock);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
