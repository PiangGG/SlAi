// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerState.h"

#include "Data/SlAiDataHandle.h"

ASlAiPlayerState::ASlAiPlayerState()
{
	//当前选中的快捷栏
	CurrentShortcutInfoIndex = 0;
}

void ASlAiPlayerState::RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList,
                                                 TSharedPtr<STextBlock> ShortcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShortcutContainer>>::TIterator It(*ContainerList);It;++It)
	{
		ShortcutContainerList.Add(*It);
	}
	ShortcutInfoTextAttr.BindUObject(this,&ASlAiPlayerState::GetShortcutInfoText);
	//绑定快捷栏信息
	ShortcutInfoTextBlock->SetText(ShortcutInfoTextAttr);

	/*
	 * 临时测试代码
	 */
	ShortcutContainerList[1]->SetObject(1)->SetObjectNum(5);
	ShortcutContainerList[2]->SetObject(2)->SetObjectNum(4);
	ShortcutContainerList[3]->SetObject(3)->SetObjectNum(3);
	ShortcutContainerList[7]->SetObject(7)->SetObjectNum(1);
}

void ASlAiPlayerState::ChoosedShortcut(bool isPre)
{
	//下一个被选择容器的下标
	int NextIndex = 0;
	if (isPre)
	{
		NextIndex =CurrentShortcutInfoIndex-1<0?8:CurrentShortcutInfoIndex-1;
	}else
	{
		NextIndex = CurrentShortcutInfoIndex+1>8?0:CurrentShortcutInfoIndex+1;
	}
	ShortcutContainerList[CurrentShortcutInfoIndex]->SetChoosed(false);
	ShortcutContainerList[NextIndex] ->SetChoosed(true);
	CurrentShortcutInfoIndex=NextIndex;
}

int ASlAiPlayerState::GetCurrentHandObjectIndex() const
{
	if (ShortcutContainerList.Num()==0)return  0;
	
	return ShortcutContainerList[CurrentShortcutInfoIndex]->ObjectIndex;
}

EObjectType::Type ASlAiPlayerState::GetCurrentObjectType()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	return ObjectAttr->ObjectType;
}

void ASlAiPlayerState::RegisterRayInfoEvent(TSharedPtr<STextBlock> RayInfoTextBlock)
{
	RayInfoTexAttr.BindUObject(this,&ASlAiPlayerState::GetRayInfoText);
	RayInfoTextBlock->SetText(RayInfoTexAttr);
}

FText ASlAiPlayerState::GetShortcutInfoText() const
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());

	switch (SlAiDataHandle::Get()->CurrentCultrueTeam)
	{
	case ECultureTeam::EN: return ObjectAttr->EN;
	case ECultureTeam::ZH: return ObjectAttr->ZH;
	}
	return ObjectAttr->EN;
}

FText ASlAiPlayerState::GetRayInfoText() const
{
	return FText::FromString("HHH");
}

