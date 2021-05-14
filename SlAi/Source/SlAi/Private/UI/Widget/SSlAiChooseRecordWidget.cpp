// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiChooseRecordWidget.h"
#include "SlateOptMacros.h"
#include "Data/SlAiDataHandle.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/STextComboBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiChooseRecordWidget::Construct(const FArguments& InArgs)
{
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	//初始化下拉菜单
	for(TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList);It;++It)
	{
		Optionssource.Add(MakeShareable(new FString(*It)));
	}
	ChildSlot
	[
		SNew(SBox)
		.WidthOverride(500.f)
		.HeightOverride(100.f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuItemBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(20.0f,0.0f,0.0f,0.0f))
			[
				SNew(STextBlock)
				.Font(MenuStyle->Font_40)
				.Text(NSLOCTEXT("SlAiMenu","ChooseRecord","ChooseRecord"))
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.0f,0.0f,20.0f,0.0f))
			[
				SNew(SBox)
				.WidthOverride(300.0f)
				.HeightOverride(60.0f)
				[
					SAssignNew(RecordComboBox,STextComboBox)
					.Font(MenuStyle->Font_30)
					.OptionsSource(&Optionssource)
				]
				
			]
		]
		
		// Populate the widget
	];
	//设置默认选项
	if (Optionssource[0])
	{
		RecordComboBox->SetSelectedItem(Optionssource[0]);
	}
}

void SSlAiChooseRecordWidget::UpdataRecordName()
{
	//修改存档名
	SlAiDataHandle::Get()->RecordName= *RecordComboBox->GetSelectedItem().Get();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
