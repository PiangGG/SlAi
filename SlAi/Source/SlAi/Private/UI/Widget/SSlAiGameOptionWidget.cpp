// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiGameOptionWidget.h"
#include "SlateOptMacros.h"
#include "Data/SlAiDataHandle.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameOptionWidget::Construct(const FArguments& InArgs)
{
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.HeightOverride(300.0f)
		.WidthOverride(500.0f)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&MenuStyle->GameOptionBGBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(50.0f))
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					[
						SAssignNew(ZhCheckBox,SCheckBox)
						.OnCheckStateChanged(this,&SSlAiGameOptionWidget::ZhCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu","Chinese","Chinese"))
							
						]
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					.FillWidth(1.0f)
					[
						SAssignNew(EnCheckBox,SCheckBox)
						.OnCheckStateChanged(this,&SSlAiGameOptionWidget::EnCheckBoxStateChanged)
						[
							SNew(STextBlock)
							.Font(MenuStyle->Font_40)
							.ColorAndOpacity(MenuStyle->FontColor_Black)
							.Text(NSLOCTEXT("SlAiMenu","English","English"))
							
						]
					]
				]
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SOverlay)
				]
				+SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillHeight(1.0f)
				[
					SNew(SOverlay)
				]
			]
		]
	];
	StyleInitialized();
}

void SSlAiGameOptionWidget::StyleInitialized()
{
	//设置zncheckbox样式
	ZhCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBursh);
	ZhCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBursh);
	ZhCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBursh);
	
	ZhCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBursh);
	ZhCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBursh);
	ZhCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBursh);

	//设置zncheckbox样式
	EnCheckBox->SetUncheckedImage(&MenuStyle->UnCheckedBoxBursh);
	EnCheckBox->SetUncheckedHoveredImage(&MenuStyle->UnCheckedBoxBursh);
	EnCheckBox->SetUncheckedPressedImage(&MenuStyle->UnCheckedBoxBursh);
	
	EnCheckBox->SetCheckedImage(&MenuStyle->CheckedBoxBursh);
	EnCheckBox->SetCheckedHoveredImage(&MenuStyle->CheckedBoxBursh);
	EnCheckBox->SetCheckedPressedImage(&MenuStyle->CheckedBoxBursh);

	switch(SlAiDataHandle::Get()->CurrentCultrueTeam)
	{
		case ECultureTeam::EN:
			{
				ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
				EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
				break;
			}
		case ECultureTeam::ZH:
			{
				ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
				EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
				break;
			}	
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiGameOptionWidget::ZhCheckBoxStateChanged(ECheckBoxState NewState)
{
	//设置被选中的框
	ZhCheckBox->SetIsChecked(ECheckBoxState::Checked);
	EnCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	//告诉数据控制类转换为中文
	SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::ZH);
}

void SSlAiGameOptionWidget::EnCheckBoxStateChanged(ECheckBoxState NewState)
{
	//设置被选中的框
	ZhCheckBox->SetIsChecked(ECheckBoxState::Unchecked);
	EnCheckBox->SetIsChecked(ECheckBoxState::Checked);
	//告诉数据控制类转换为英文
	SlAiDataHandle::Get()->ChangeLocalizationCulture(ECultureTeam::EN);
}