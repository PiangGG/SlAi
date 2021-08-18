// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerState.h"

#include "Data/SlAiDataHandle.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SlAiPlayerController.h"

ASlAiPlayerState::ASlAiPlayerState()
{
	//允许每帧运行
	PrimaryActorTick.bCanEverTick = true;
	//当前选中的快捷栏
	CurrentShortcutInfoIndex = 0;
	HP = 500.0f;
	Hunger = 600.0f;
}

void ASlAiPlayerState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//如果饥饿值为0，持续减血
	if(Hunger<=0)
	{
		 HP-=DeltaSeconds*2;
	}else
	{
		Hunger-=DeltaSeconds*2;
		HP+=DeltaSeconds*1;
	}
	//设定范围
	HP = FMath::Clamp<float>(HP,0,500.0f);
	Hunger = FMath::Clamp<float>(Hunger,0,600.0f);
	//执行修改玩家状态UI的委托
	UpdateStateWidget.ExecuteIfBound(HP/500.0f,Hunger/600.0f);
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
	/*ShortcutContainerList[1]->SetObject(1)->SetObjectNum(5);
	ShortcutContainerList[2]->SetObject(2)->SetObjectNum(4);
	ShortcutContainerList[3]->SetObject(3)->SetObjectNum(3);
	ShortcutContainerList[7]->SetObject(7)->SetObjectNum(1);
	ShortcutContainerList[4]->SetObject(6)->SetObjectNum(1);
	ShortcutContainerList[5]->SetObject(5)->SetObjectNum(1);*/
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

int ASlAiPlayerState::GetAffectRange()
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	//获取当前手上物品的作用范围
	return ObjectAttr->AffectRange;
}

int ASlAiPlayerState::GetDamageValue(EResourceType::Type ResourceType)
{
	TSharedPtr<ObjectAttribute> ObjectAttr;
	ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(GetCurrentHandObjectIndex());
	
	switch (ResourceType)
	{
		case EResourceType::Plant: 
			return ObjectAttr->PlantAttck;
		case EResourceType::Metal: 
			return ObjectAttr->MetalAttck;
		case EResourceType::Animl:
			return ObjectAttr->AnimalAttck;
	}
	return ObjectAttr->PlantAttck;
}

void ASlAiPlayerState::ChangeHandObject(int ShortcoutID, int ObjectID, int ObjectNum)
{
	//更改快捷欄信息
	ShortcutContainerList[ShortcoutID]->SetObject(ObjectID)->SetObjectNum(ObjectNum);
	//告訴controller更新一次手持物品
	SPController->ChangeHandObject();
}

void ASlAiPlayerState::ProomoteHunger()
{
	//只要超过500,马上设置为600
	if (Hunger+100>500.0f)
	{
		Hunger = 600.0f;
		return;
	}
	//否则只加100
	Hunger = FMath::Clamp<float>(Hunger+100.0f,0,600.0f);
}

bool ASlAiPlayerState::IsPlayerDead()
{
	return HP<=0.0f;
}

void ASlAiPlayerState::BeginPlay()
{
	Super::BeginPlay();
	SPController = Cast<ASlAiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	
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
	return RayInfoText;
}

