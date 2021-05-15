// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSlAiChooseRecordWidget.h"
#include "SSlAiGameOptionWidget.h"
#include "SSlAiNewGameWidget.h"
#include "Data/SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"


/**
 * 
 */
struct MenuGroup;
class SBox;
class STextBlock;
class SLAI_API SSlAiMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMenuWidget)
	{}
	SLATE_END_ARGS()
		
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
private:
	//绑定到各个MenuItem的函数
	void MenuItemOnclicked(EMenuItem::Type ItemType);

	//修改语言
	void ChangeCulture(ECultureTeam CultureTeam);
	//修改音量|声音
	void ChangeVolume(const float MusicVolume,const float SoundVolume);
	//初始化所有控件
	void InitializedMenuList();
	//选择显示的界面
	void ChooseWidget(EMenuType::Type WidgetType);
	//修改菜单高度
	void ReSetWidgetSize(float NewWidth, float NewHeight=-1.0f);
	
private:
	//保存根节点
	TSharedPtr<SBox> RootSizeBox;
	//获取MenuStyle
	const struct FSlAiMenuStyle *MenuStyle;
	//标题文字
	TSharedPtr<STextBlock> TitleText;
	//垂直框|用来保存垂直列表
	TSharedPtr<SVerticalBox>ContentBox;
	//保存菜單組
	TMap<EMenuType::Type,TSharedPtr<MenuGroup>> MenuMap;
	//游戲設置widget的指引
	TSharedPtr<SSlAiGameOptionWidget> GameOptionWidget;
	//新游戲控件
	TSharedPtr<SSlAiNewGameWidget> NewGameWidget;
	//選擇存檔的空間指針
	TSharedPtr<SSlAiChooseRecordWidget> ChooseRecordWidget;
	
};
