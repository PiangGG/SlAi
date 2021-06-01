// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiPackageWidget.h"
#include "SlateOptMacros.h"
#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "Player/SlAiPackageManager.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "UI/Widget/Package/SSlAiContainerBaseWidget.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPackageWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	UIScaler=InArgs._UIScaler;
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
	MousePosition = FVector2D(0.0f,0.0f);

	IsInitPackageMana = false;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiPackageWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//如果背包显示并且世界存在,实时更新鼠标位置
	if (GetVisibility()==EVisibility::Visible&&GEngine)
	{
		GEngine->GameViewport->GetMousePosition(MousePosition);
		SlAiHelper::Debug(FString("APos"+MousePosition.ToString()),0.f);
		MousePosition = MousePosition/UIScaler.Get();
		SlAiHelper::Debug(FString("RPos"+MousePosition.ToString()),0.f);
	}

	//如果背包管理器已经初始化
	if (IsInitPackageMana)
	{
		//实时更新容器是否悬停
		SlAiPackageManager::Get()->UpdateHovered(MousePosition,AllottedGeometry);
	}
}

int32 SSlAiPackageWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	//先调用父类
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
	//如果背包管理没有初始化
	if (!IsInitPackageMana)return LayerId;

	//如果背包管理器的手上物品不等于0，就进行渲染
	if (GetVisibility()==EVisibility::Visible&&SlAiPackageManager::Get()->ObjectIndex!=0&&SlAiPackageManager::Get()->ObjectNum!=0)
	{
		//渲染物品
		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId+30,
			AllottedGeometry.ToPaintGeometry(MousePosition-FVector2D(32.0f,32.0f),FVector2D(64.0f,64.0f)),
			SlAiDataHandle::Get()->ObjectBrushList[SlAiPackageManager::Get()->ObjectIndex],
			ESlateDrawEffect::None,
			FLinearColor(1.0f,1.0f,1.0f,1.0f)
		);

		//获取物品属性
		TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(SlAiPackageManager::Get()->ObjectIndex);
		//渲染数量
		if (ObjectAttr->ObjectType!=EObjectType::Tool&&ObjectAttr->ObjectType!=EObjectType::Weapon)
		{
			//渲染数量
			FSlateDrawElement::MakeText
			(
				OutDrawElements,
				LayerId+30,
				AllottedGeometry.ToPaintGeometry(MousePosition+FVector2D(12.0f,16.0f),FVector2D(16.0,16.0)),
				FString::FromInt(SlAiPackageManager::Get()->ObjectNum),
				GameStyle->Font_16,
				ESlateDrawEffect::None,
				GameStyle->FontColor_Black
			);
		}
	}
	return LayerId;
}

FReply SSlAiPackageWidget::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	//如果背包没有初始化
	if (!IsInitPackageMana)return FReply::Handled();

	//如果是左键点击
	if ( MouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		SlAiPackageManager::Get()->LeftOption(MousePosition,MyGeometry);
	}
	if ( MouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		SlAiPackageManager::Get()->RightOption(MousePosition,MyGeometry);
	}
	return FReply::Handled();
}


void SSlAiPackageWidget::InitPackageManager()
{
	//SlAiHelper::Debug(FString("InitPackageManager"));
	//初始化快捷栏
	for(int i=0;i<9;++i)
	{
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Shortcut,i);
		//将容器实例添加到UI
		ShortcutGrid->AddSlot(i,0)[NewContainer->AsShared()];
		SlAiPackageManager::Get()->InsertContainer(NewContainer,EContainerType::Shortcut);
	}

	//背包主体
	for (int i = 0;i < 36;++i)
	{
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Normal,i);
		PackageGrid->AddSlot(i%9,i/9)[NewContainer->AsShared()];
		SlAiPackageManager::Get()->InsertContainer(NewContainer,EContainerType::Normal);
	}

	//初始化合成台
	for (int i = 0;i < 9;++i)
	{
		TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Input,i);
		CompoundGrid->AddSlot(i%3,i/3)[NewContainer->AsShared()];
		SlAiPackageManager::Get()->InsertContainer(NewContainer,EContainerType::Input);
	}
	//初始化输出容器
	TSharedPtr<SSlAiContainerBaseWidget> NewContainer = SSlAiContainerBaseWidget::CreateContainer(EContainerType::Output,1);
	OutputBorder->SetContent(NewContainer->AsShared());
	SlAiPackageManager::Get()->InsertContainer(NewContainer,EContainerType::Output);

	IsInitPackageMana = true;
}


