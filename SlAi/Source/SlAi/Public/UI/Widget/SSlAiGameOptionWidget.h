// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SCheckBox;
class SLAI_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
private:
	//统一设置样式
	void StyleInitialized();
	//中文Checkbox
	void ZhCheckBoxStateChanged(ECheckBoxState NewState);
	//英文Checkbox
	void EnCheckBoxStateChanged(ECheckBoxState NewState);
private:
	const struct FSlAiMenuStyle *MenuStyle;

	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;
};
