// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/SlAiPickUpObject.h"

// Sets default values
ASlAiPickUpObject::ASlAiPickUpObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//实例化根节点
	RootScene=CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent=RootScene;
	//实例化模型组件
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootScene);
	BaseMesh->SetCollisionProfileName(FName("PickUpProfile"));
	//开启交互检测
	BaseMesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ASlAiPickUpObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlAiPickUpObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

