// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLAI_API SlAiStyle
{
public:
	//初始化,类似单例
    static  void Initialze();
	//得到类型的名字
	static  FName GetStyleSetName();
	//关闭
	static void ShutDown();
	//得到Slate类型
	static const ISlateStyle& Get();
private:
	//注册样式
	static TSharedRef<class FSlateStyleSet> Create(); //注册类的样式
	static TSharedPtr<class FSlateStyleSet> SlAiStyleInstance;//SlateStyle实例
};
