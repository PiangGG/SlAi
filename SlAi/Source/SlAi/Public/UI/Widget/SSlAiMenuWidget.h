// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"


/**
 * 
 */
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
	
private:
	//保存根节点
	TSharedPtr<SBox> RootSizeBox;
	//获取MenuStyle
	const struct FSlAiMenuStyle *MenuStyle;
	//标题文字
	TSharedPtr<STextBlock> TitleText;

	//垂直框|用来保存垂直列表
	TSharedPtr<SVerticalBox>ContentBox;
};
