// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "GameFramework/PlayerState.h"
#include "SlAiPlayerState.generated.h"

/**
 * 
 */
//更新玩家状态UI委托
DECLARE_DELEGATE_TwoParams(FUpdateStateWidget,float,float)
UCLASS()
class SLAI_API ASlAiPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASlAiPlayerState();

	virtual  void Tick(float DeltaSeconds) override;
	//提供给ShortcutWidget的添加快捷栏容器委托
	void RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList,TSharedPtr<STextBlock>ShortcutInfoTextBlock);
	//切换快捷栏
	void ChoosedShortcut(bool isPre);
	//获取容器物品内容的Index
	int GetCurrentHandObjectIndex()const;
	//获取当前手持物品的物品类型
	EObjectType::Type GetCurrentObjectType();
	//提供给RayInfoWidget的射线注册信息事件
	void RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock);

	//获取手上物品的攻击范围
	int GetAffectRange();
	//获取伤害值
	int GetDamageValue(EResourceType::Type ResourceType);
public:
	//当被选中的快捷栏序号
	int CurrentShortcutInfoIndex;
	//射线检测信息TEXT,由PlayerController更新
	FText RayInfoText;
	//更新玩家状态UI,绑定的方法是PlayerStateWidget的UpdateStateWidget
	FUpdateStateWidget UpdateStateWidget;
private:
	//获取快捷栏物品信息
	FText GetShortcutInfoText()const;
	//获取射线检测信息
	FText GetRayInfoText()const;
private:
	//快捷栏序列
	TArray<TSharedPtr<ShortcutContainer>> ShortcutContainerList;

	//快捷栏信息参数
	TAttribute<FText> ShortcutInfoTextAttr;
	//射线信息参数
	TAttribute<FText> RayInfoTexAttr;
	//血值|饥饿度
	float HP;
	float Hunger;
};
