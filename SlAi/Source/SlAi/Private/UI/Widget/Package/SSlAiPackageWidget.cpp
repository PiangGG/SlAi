// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiPackageWidget.h"
#include "SlateOptMacros.h"
#include "Common/SlAiHelper.h"
#include "Player/SlAiPackageManager.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "UI/Widget/Package/SSlAiContainerBaseWidget.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPackageWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SOverlay)
		//背包
		+SOverlay::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Right)
		.Padding(FMargin(0.0f,0.0f,50.0f,0.0f))
		[
			SNew(SBox)
			.WidthOverride(800.0f)
			.HeightOverride(800.0f)
			[
				SNew(SOverlay)

				//背景图
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(&GameStyle->PackageBGBrush)
				]
				+SOverlay::Slot()//底部快捷栏
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.0f,680.0f,40.f,40.0f))
				[
					SAssignNew(ShortcutGrid,SUniformGridPanel)
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(40.0f,320.f,40.0f,160.0f))
				[
					SAssignNew(PackageGrid,SUniformGridPanel)
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(80.0f,40.f,480.0f,520.0f))
				[
					SAssignNew(CompoundGrid,SUniformGridPanel)
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(560.0f,120.0f,160.0f,600.0f))
				[
					SAssignNew(OutputBorder,SBorder)
				]
				//合成小箭头
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(FMargin(400.0f,120.0f,320.0f,600.0f))
				[
					SNew(SImage)
					.Image(&GameStyle->CompoundArrowBrush)
				]
			]
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiPackageWidget::InitPackageManager()
{
	//SlAiHelper::Debug(FString("InitPackageManager"));
	//初始化快捷栏
	for(int i=0;i<9;++i)
	{
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Shortcut,i);
		//将容器实例添加到UI
		ShortcutGrid->AddSlot(i,0)[NewContainer->AsShared()];
	}

	//背包主体
	for (int i = 0;i < 36;++i)
	{
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Normal,i);
		PackageGrid->AddSlot(i%9,i/9)[NewContainer->AsShared()];
		//SlAiPackageManager::Get()->InSertContainer(NewContainer,EContainerType::Normal);
	}

	//初始化合成台
	for (int i = 0;i < 9;++i)
	{
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Input,i);
		CompoundGrid->AddSlot(i%3,i/3)[NewContainer->AsShared()];
		//SlAiPackageManager::Get()->InSertContainer(NewContainer,EContainerType::Normal);
	}
	//初始化输出容器
	TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Output,1);
	OutputBorder->SetContent(NewContainer->AsShared());
		
}


