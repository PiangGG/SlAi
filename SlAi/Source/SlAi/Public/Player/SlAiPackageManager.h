// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UI/Widget/Package/SSlAiContainerBaseWidget.h"

/**
 * 
 */
class SLAI_API SlAiPackageManager
{
public:
	SlAiPackageManager();
	static void Initialize();
	static TSharedPtr<SlAiPackageManager> Get();
	//添加容器
	void InsertContainer(TSharedPtr<class SSlAiContainerBaseWidget> Container,EContainerType::Type InsertType);
	//更新悬停容器颜色
	void UpdateHovered(FVector2D MousePos,FGeometry PackGeo);

	//左键事件,参数是鼠标位置和PackageWidget的Geometry
	void LeftOption(FVector2D MousePos,FGeometry PackGeo);
	//右键事件,参数是鼠标位置和PackageWidget的Geometry
	void RightOption(FVector2D MousePos,FGeometry PackGeo);
public:
	//鼠标物品ID
	int ObjectIndex;
	//鼠标物品数量
	int ObjectNum;
private:
	//创建实例
	static TSharedRef<SlAiPackageManager> Create();
	//获取鼠标指向容器
	TSharedPtr<SSlAiContainerBaseWidget> LocateContainer(FVector2D MousePos,FGeometry PackGeo);
private:
	//单例指针
	static TSharedPtr<SlAiPackageManager> PackageInstance;

	//容器列表
	TArray<TSharedPtr<SSlAiContainerBaseWidget>> InputContainerList;
	TArray<TSharedPtr<SSlAiContainerBaseWidget>> NormalContainerList;
	TArray<TSharedPtr<SSlAiContainerBaseWidget>> ShortcutContainerList;
	//输出容器
	TSharedPtr<SSlAiContainerBaseWidget> OutputContainer;
	//上一个悬停容器
	TSharedPtr<SSlAiContainerBaseWidget> LastHoveredCon;
};
