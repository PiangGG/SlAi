// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "GameFramework/PlayerState.h"
#include "SlAiPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API ASlAiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASlAiPlayerState();

	//提供给ShortcutWidget的添加快捷栏容器委托
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList,TSharedPtr<STextBlock>ShortcutInfoTextBlock);
	//切换快捷栏
	void ChoosedShortcut(bool isPre);
	//获取容器物品内容的Index
	int GetCurrentHandObjectIndex()const;
	//获取当前手持物品的物品类型
	EObjectType::Type GetCurrentObjectType();
public:
	//当被选中的快捷栏序号
	int CurrentShortcutInfoIndex;
private:
	//获取快捷栏物品信息
	FText GetShortcutInfoText()const;
private:
	//快捷栏序列
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	//快捷栏信息参数
	TAttribute<FText> ShortcutInfoTextAttr;
	
};
