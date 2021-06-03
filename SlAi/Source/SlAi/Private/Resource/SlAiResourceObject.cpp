// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource/SlAiResourceObject.h"

#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "Data/SlAiTypes.h"
#include "Flob/SlAiFlobObject.h"

// Sets default values
ASlAiResourceObject::ASlAiResourceObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//实例化根节点
	RootScene=CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent=RootScene;
	//实例化模型组件
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);
	BaseMesh->SetCollisionProfileName(FName("ResourceProfile"));

	//开启交互检测
	BaseMesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ASlAiResourceObject::BeginPlay()
{
	Super::BeginPlay();
	//TSharedPtr<ResourceAttribute> ResourceAttr=*SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//HP=BaseHP=2000;//ResourceAttr->HP;
	//这段有问题
	//TSharedPtr<ResourceAttribute> ResourceAttr=*SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//HP = BaseHP = ResourceAttr->HP;
	HP = BaseHP=200;
}

void ASlAiResourceObject::CreateFlobObject()
{
	TSharedPtr<ResourceAttribute> ResourceAttr = *SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	//遍历生成掉落物
	for (TArray<TArray<int>>::TIterator It(ResourceAttr->FlobObjectInfo);It;++It)
	{
		//随机生成的数量
		FRandomStream Stream;
		Stream.GenerateNewSeed();
		//生成数量
		int Num = Stream.RandRange((*It)[1],(*It)[2]);
		if (GetWorld())
		{
			for (int i = 0;i<Num;++i)
			{
				//生成掉落物
				ASlAiFlobObject* FlobObject = GetWorld()->SpawnActor<ASlAiFlobObject>(GetActorLocation()+FVector(0.0f,0.0f,20.0f),FRotator::ZeroRotator);
				FlobObject->CreateFlobObject((*It)[0]);
			}
		}
	}
}

// Called every frame
void ASlAiResourceObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FText ASlAiResourceObject::GetInfoText() const
{
	TSharedPtr<ResourceAttribute> ResourceAttr=*SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	switch (SlAiDataHandle::Get()->CurrentCultrueTeam)
	{
		case ECultureTeam::EN: return ResourceAttr->EN;
		case ECultureTeam::ZH: return ResourceAttr->ZH;
	}
	return ResourceAttr->ZH;
}

EResourceType::Type ASlAiResourceObject::GetResourceType()
{
	TSharedPtr<ResourceAttribute> ResourceAttr=*SlAiDataHandle::Get()->ResourceAttrMap.Find(ResourceIndex);
	return ResourceAttr->ResourceType;
}

float ASlAiResourceObject::GetHPRange()
{
	return FMath::Clamp<float>((float)HP/(float)BaseHP,0.0f,1.0f);
}

ASlAiResourceObject* ASlAiResourceObject::TakeObjectDamage(int Damge)
{
	HP = FMath::Clamp<int>(HP-Damge,0,BaseHP);
	//如果小于0
	if (HP<=0)
	{
		BaseMesh->SetCollisionResponseToChannels(ECR_Ignore);
		//创建掉落物
		CreateFlobObject();
		
		GetWorld()->DestroyActor(this);
	}
	return this;
}

int ASlAiResourceObject::GetResourceIndex()
{
	return ResourceIndex;
}

