// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLAI_API SSlAiShortcutWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiShortcutWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
private:
	//初始化所有容器
	void InitializeContainer();
private:
	//获取GameStyle
	const struct FSlAiGameStyle *GameStyle;

	//物品信息指针
	TSharedPtr<class STextBlock> ShorcutInfoTextBlock;
	
	//网格指针SUniformGridPanel
	TSharedPtr<class SUniformGridPanel> GaidPanel;

	//是否初始化容器
	bool IsInitializeContainer;
};
