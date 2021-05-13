// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSlider.h"

//修改中英文委托
DECLARE_DELEGATE_OneParam(FChangeCulture,const ECultureTeam)
//修改音量的魏国
DECLARE_DELEGATE_TwoParams(FChangeVolume,const float,const float)
/**
 * 
 */
class SCheckBox;
class SSlider;
class SLAI_API SSlAiGameOptionWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameOptionWidget)
	{}
	SLATE_EVENT(FChangeCulture,ChangeCulture)
	SLATE_EVENT(FChangeVolume,ChangeVolume)
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

	//音量变化事件
	void MusicSliderChanged(float value);
	void SoundSliderChanged(float value);
private:
	const struct FSlAiMenuStyle *MenuStyle;

	TSharedPtr<SCheckBox> EnCheckBox;
	TSharedPtr<SCheckBox> ZhCheckBox;

	//两个进度条
	TSharedPtr<SSlider> MuSlider;//背景音乐
	TSharedPtr<SSlider> SoSlider;//音效
	//进度条指针
	TSharedPtr<STextBlock> MuTextBlock;
	TSharedPtr<STextBlock> SoTextBlock;

	//委托变量
	FChangeCulture ChangeCulture;
	FChangeVolume ChangeVolume;
};
