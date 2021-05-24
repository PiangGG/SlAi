// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLAI_API SSlAiPointerWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiPointerWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	//给PlayerController绑定事件,修改准心是否锁定以及加载进度
	void UpdatePointer(bool IsAim,float Range);
private:
	//给SBox大小变化绑定函数
	FOptionalSize GetBoxWidget()const ;
	FOptionalSize GetBoxHeight()const;
	
private:
	//获取GameStyle
	const struct FSlAiGameStyle* GameStyle;
	
	TSharedPtr<class SBox>RootBox;

	float CurrentSize;

	//获取材质实例
	class UMaterialInstanceDynamic *PointerMaterial;
	//是否改变大小
	bool IsAimed;
};
