// Fill out your copyright notice in the Description page of Project Settings.


#include "Resource/SlAiResourceObject.h"

#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "Data/SlAiTypes.h"

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
	HP=BaseHP=2000;//ResourceAttr->HP;
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
		GetWorld()->DestroyActor(this);
	}
	return this;
}

