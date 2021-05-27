// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLAI_API SSlAiGameHUDWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiGameHUDWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	//绑定到UIScaler
    float GetUIScaler()const;
public:
	//快捷栏指针
	TSharedPtr<class SSlAiShortcutWidget> ShortcutWidget;
	//射线信息框指针
	TSharedPtr<class SSlAiRayInfoWidget> RayInfoWidget;
	//准心
	TSharedPtr<class SSlAiPointerWidget> PointerWidget;	
	//玩家状态指针
	TSharedPtr<class SSlAiPlayerStateWidget> PlayerStateWidget;
private:
	//获取屏幕size
	FVector2D GetViewporSize()const;
private:
	//DPI缩放
	TAttribute<float> UIScaler;

	
};
