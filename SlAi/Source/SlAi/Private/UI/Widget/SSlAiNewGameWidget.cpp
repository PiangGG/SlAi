// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiNewGameWidget.h"
#include "SlateOptMacros.h"
#include "Data/SlAiDataHandle.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Input/SEditableTextBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiNewGameWidget::Construct(const FArguments& InArgs)
{
	
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

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
				.Text(NSLOCTEXT("SlAiMenu","NewGame","NewGame"))
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
					SAssignNew(EditTextBox,SEditableTextBox)
					.HintText(NSLOCTEXT("SlAiMenu","RepeatedNameHint","Input Record Name!"))
					.Font(MenuStyle->Font_30)
				]
				
			]
		]
		
		// Populate the widget
	];
	
}

bool SSlAiNewGameWidget::AllowEnterGame()
{
	//获取新存档名
	FText InputText=EditTextBox->GetText();
	//判断文字是否为空
	if (InputText.ToString().IsEmpty())return false;
	//查询是否存在相同存档
	for(TArray<FString>::TIterator It(SlAiDataHandle::Get()->RecordDataList);It;++It)
	{
		if ((*It).Equals(InputText.ToString()))
		{
			//设置输入框为空
			EditTextBox->SetText(FText::FromString(""));
			//修改Tint为存档名存在
			EditTextBox->SetHintText(NSLOCTEXT("SlAiMenu","NameRepeatedHint","Record Name Repeated!"));
			return false;
		}
	}
	//保存新的存档名
	SlAiDataHandle::Get()->RecordName = InputText.ToString();

	return true;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
