// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuWidget.h"
#include "SlateOptMacros.h"
#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "Data/SlAiTypes.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "UI/Widget/SSlAiChooseRecordWidget.h"
#include "Widgets/Images/SImage.h"
#include "UI/Widget/SSlAiMenuItemWidget.h"
#include "UI/Widget/SSlAiGameOptionWidget.h"
#include "UI/Widget/SSlAiNewGameWidget.h"

struct MenuGroup
{
	//菜單標題
	FText MenuName;
	//菜單高度
	float MenuHeight;
	//下屬組件
	TArray<TSharedPtr<SCompoundWidget>> ChildWidget;
	//構造函數
	MenuGroup(const FText Name,const float Height,
		TArray<TSharedPtr<SCompoundWidget>>* Children)
	{
		MenuName=Name;
		MenuHeight=Height;
		for(TArray<TSharedPtr<SCompoundWidget>>::TIterator It(*Children);It;++It)
		{
			ChildWidget.Add(*It);
		}
		//ChildWidget=*Children;
	}
};

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuWidget::Construct(const FArguments& InArgs)
{
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

	ChildSlot
	[
		// Populate the widget
		SAssignNew(RootSizeBox,SBox)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.Padding(FMargin(0.0f,50.0f,0.0f,0.0f))
			[
				SNew(SImage)
				.Image(&MenuStyle->MenuBackgroundBrush)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.0f,25.0f,0.0f,0.0f))
			[
				SNew(SImage)
				.Image(&MenuStyle->LeftIconBruch)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.Padding(FMargin(0.0f,25.0f,0.0f,0.0f))
			[
				SNew(SImage)
				.Image(&MenuStyle->RightIconBruch)
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBox)
				.WidthOverride(400.0f)
				.HeightOverride(100.0f)
				[
					SNew(SBorder)
					.BorderImage(&MenuStyle->TitleBorderBrush)
					.HAlign(HAlign_Center)
					.VAlign(VAlign_Center)
					[
					SAssignNew(TitleText, STextBlock)//标题
					//.Font(SlAiStyle::Get().GetFontStyle("MenuItemFont"))
					//.Text(FText::FromString("I am 12"))
					.Text(NSLOCTEXT("SlAiMenu", "Menu", "Menu"))//文字本地化
					]
				]
			]
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			.Padding(FMargin(0.0f,130.0f,0.0f,0.0f))
			[
				SAssignNew(ContentBox,SVerticalBox)
				
			]
		]
	];
	
	if (ContentBox)
	{
		InitializedMenuList();
	}
}

void SSlAiMenuWidget::MenuItemOnclicked(EMenuItem::Type ItemType)
{
	SlAiHelper::Debug("MenuItemOnclicked");
}

void SSlAiMenuWidget::ChangeCulture(ECultureTeam CultureTeam)
{
	SlAiDataHandle().Get()->ChangeLocalizationCulture(CultureTeam);
}

void SSlAiMenuWidget::ChangeVolume(const float MusicVolume, const float SoundVolume)
{
	SlAiDataHandle().Get()->ResetMenuVolume(MusicVolume,SoundVolume);
}

void SSlAiMenuWidget::InitializedMenuList()
{
	if (&MenuStyle->Font_60&&TitleText)
	{
		TitleText->SetFont(FSlateFontInfo(MenuStyle->Font_60));
	}
	//實例化主界面
	TArray<TSharedPtr<SCompoundWidget>> MainMenuList;
	MainMenuList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","StartGame","StartGame"))
		.ItemType(EMenuItem::StartGame)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MainMenuList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","GameOption","GameOption"))
		.ItemType(EMenuItem::GameOption)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MainMenuList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","QuitGame","QuitGame"))
		.ItemType(EMenuItem::QuitGame)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MenuMap.Add(EMenuType::MainMenu,MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu","Menu","Menu"),510.f,&MainMenuList)));

	//開始界面
	TArray<TSharedPtr<SCompoundWidget>> StartGameList;
	StartGameList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","NewGame","NewGame"))
		.ItemType(EMenuItem::NewGame)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	StartGameList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","LoadRecord","LoadRecord"))
		.ItemType(EMenuItem::LoadRecord)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	StartGameList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","GoBack","GoBack"))
		.ItemType(EMenuItem::StartGameGoBack)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MenuMap.Add(EMenuType::StartGame,MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu","StartGame","StartGame"),510.f,&StartGameList)));

	//游戲設置界面
	TArray<TSharedPtr<SCompoundWidget>> GameOptionList;
	//实例化游戏设置的界面Wiget
	SAssignNew(GameOptionWidget,SSlAiGameOptionWidget)
	.ChangeCulture(this,&SSlAiMenuWidget::ChangeCulture)
	.ChangeVolume(this,&SSlAiMenuWidget::ChangeVolume);
	//添加控件到数组
	GameOptionList.Add(GameOptionWidget);
	//添加返回按钮
	GameOptionList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","GoBack","GoBack"))
		.ItemType(EMenuItem::GameOptionGoBack)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MenuMap.Add(EMenuType::GameOption,MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu","GameOption","GameOption"),610.f,&GameOptionList)));

	//开始新游戏界面
	TArray<TSharedPtr<SCompoundWidget>> NewGameList;
	SAssignNew(NewGameWidget,SSlAiNewGameWidget);
	NewGameList.Add(NewGameWidget);
	NewGameList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","EnterGame","EnterGame"))
		.ItemType(EMenuItem::EnterGame)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	NewGameList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","GoBack","GoBack"))
		.ItemType(EMenuItem::StartGameGoBack)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MenuMap.Add(EMenuType::NewGame,MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu","NewGame","NewGame"),510.f,&NewGameList)));

	//选择存档界面
	TArray<TSharedPtr<SCompoundWidget>> ChooseRecordList;
	SAssignNew(ChooseRecordWidget,SSlAiChooseRecordWidget);
	ChooseRecordList.Add(ChooseRecordWidget);
	ChooseRecordList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","EnterRecord","EnterRecord"))
		.ItemType(EMenuItem::EnterRecord)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	NewGameList.Add(SNew(SSlAiMenuItemWidget)
		.ItemText(NSLOCTEXT("SlAiMenu","GoBack","GoBack"))
		.ItemType(EMenuItem::ChooseRecordGoBack)
		.OnClicked(this,&SSlAiMenuWidget::MenuItemOnclicked));
	MenuMap.Add(EMenuType::ChooseRecord,MakeShareable(new MenuGroup(NSLOCTEXT("SlAiMenu","ChooseRecord","ChooseRecord"),510.f,&ChooseRecordList)));

	ChooseWidget(EMenuType::MainMenu);
}

void SSlAiMenuWidget::ChooseWidget(EMenuType::Type WidgetType)
{
	//移除所有组件
	ContentBox->ClearChildren();
	//如果传入Type是None直接返回
	if (WidgetType==EMenuType::None)
	{
		return;;
	}
	for (TArray<TSharedPtr<SCompoundWidget>>::TIterator It((*MenuMap.Find(WidgetType))->ChildWidget);It;++It)
	{
		ContentBox->AddSlot().AutoHeight()[(*It)->AsShared()];
	}
	//更改标题
	TitleText->SetText((*MenuMap.Find(WidgetType))->MenuName);
	//修改Size
	ReSetWidgetSize(600.0f,(*MenuMap.Find(WidgetType))->MenuHeight);
}

//如果高度不修改，传入-1
void SSlAiMenuWidget::ReSetWidgetSize(float NewWidth, float NewHeight)
{
	RootSizeBox->SetWidthOverride(NewWidth);
	if (NewHeight>0)
	{
		RootSizeBox->SetHeightOverride(NewHeight);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
