// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "SlAiMenuWidgetStyle.generated.h"

/**
 * 
 */
USTRUCT()
struct SLAI_API FSlAiMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FSlAiMenuStyle();
	virtual ~FSlAiMenuStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FSlAiMenuStyle& GetDefault();

	//整体背景图片
	UPROPERTY(EditAnywhere,Category=MenuHUD)
	FSlateBrush MenuHUDBackgroundBrush;
	//菜单背景图片
	UPROPERTY(EditAnywhere,Category=Menu)
	FSlateBrush MenuBackgroundBrush;
	//菜单左图标Bursh
	UPROPERTY(EditAnywhere,Category=Menu)
	FSlateBrush LeftIconBruch;
	//菜单右图标Bursh
	UPROPERTY(EditAnywhere,Category=Menu)
	FSlateBrush RightIconBruch;
	//菜单标题图标Bursh
	UPROPERTY(EditAnywhere,Category=Menu)
	FSlateBrush TitleBorderBrush;
	
	/*
	 * MenuItem的Bursh
	 */
	UPROPERTY(EditAnywhere,Category=Menu)
	FSlateBrush MenuItemBrush;

	/*
	 * 字体,颜色
	 */
    //UPROPERTY(EditAnywhere,Category=Menu)
    //FSlateFontInfo SlateFontInfo;
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_60;
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_40;
	UPROPERTY(EditAnywhere,Category=Common)
	FSlateFontInfo Font_30;
	UPROPERTY(EditAnywhere,Category=Common)
	FLinearColor FontColor_white;
	UPROPERTY(EditAnywhere,Category=Common)
	FLinearColor FontColor_Black;
	
	UPROPERTY(EditAnywhere,Category=GameOption)
	FSlateBrush GameOptionBGBrush;

	/**
	 * checkedBox的Bursh被选中与不被选中
	 */
	UPROPERTY(EditAnywhere,Category=GameOption)
	FSlateBrush CheckedBoxBursh;
	UPROPERTY(EditAnywhere,Category=GameOption)
	FSlateBrush UnCheckedBoxBursh;
};	

/**
 */
UCLASS(hidecategories=Object, MinimalAPI)
class USlAiMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FSlAiMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
