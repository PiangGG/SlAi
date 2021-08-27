// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "SlAiGameWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLAI_API FSlAiGameStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()
public:
	
	FSlAiGameStyle();
	virtual ~FSlAiGameStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiGameStyle& GetDefault();

	//指定快捷栏容器图标
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush NormalContainerBrush;
	//指定被选择容器的Brush
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ChoosedContainerBrush;
	//指定没有颜色的Bursh
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush EmptyBrush;
	//背包背景图
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush PackageBGBrush;
	//合成表箭头
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush CompoundArrowBrush;
	//物品Brush
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_1;
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_2;
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_3;
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_4;
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_5;
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_6;
	UPROPERTY(EditAnywhere,Category=Package)
	FSlateBrush ObjectBrush_7;

	//射线检测信息背板
	UPROPERTY(EditAnywhere,Category=Info)
	FSlateBrush RayInfoBursh;
	UPROPERTY(EditAnywhere,Category=Info)
	FSlateBrush PointerBursh;

	//小地图背景图片
	UPROPERTY(EditAnywhere,Category=MiniMap)
	FSlateBrush MiniMapBursh;
	
	UPROPERTY(EditAnywhere,Category=PlayerState)
	FSlateBrush PlayerStateBGBrush;
	UPROPERTY(EditAnywhere,Category=PlayerState)
	FSlateBrush PlayerHeadBrush;
	UPROPERTY(EditAnywhere,Category=PlayerState)
	FSlateBrush PlayerHeadBGBrush;
	UPROPERTY(EditAnywhere,Category=PlayerState)
	FSlateBrush HPBrush;
	UPROPERTY(EditAnywhere,Category=PlayerState)
	FSlateBrush HungerBrush;
	
	/*
	 * 60号字体
	 */
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_60;
	/*
	* 50号字体,有轮廓
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_Outline_50;
	/*
	* 40号字体
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_40;
	/*
	* 40号字体,有轮廓
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_Outline_40;
	/*
	* 30号字体
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_30;
	/*
	* 20号字体
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_20;
	/*
	* 20号字体,有轮廓
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_Outline_20;
	/*
	* 16号字体
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_16;
	/*
	* 16号字体,有轮廓
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_Outline_16;

	/*
	 * 黑色
	 */
	UPROPERTY(EditAnywhere,Category=Common)
	FLinearColor FontColor_Black;
	/*
	* 白色
	*/
	UPROPERTY(EditAnywhere,Category=Common)
	FLinearColor FontColor_White;
};

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiGameWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiGameStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
