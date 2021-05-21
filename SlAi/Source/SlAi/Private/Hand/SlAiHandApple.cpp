// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandApple.h"

#include "Components/BoxComponent.h"

ASlAiHandApple::ASlAiHandApple()
{
	//给模型组件添加模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Item_Fruit_02.SM_Item_Fruit_02'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeLocation(FVector(-8.0f,-3.0f,7.0f));
	BaseMesh->SetRelativeRotation(FRotator(-90.0f,0,0));
	BaseMesh->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));

	//设置碰撞体属性
	AffectCollision->SetBoxExtent(FVector(10.0f,10.0f,10.0f));
	AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,10.0f));
	//AffectCollision->SetRelativeScale3D(FVector(0.375f,0.5f,0.135f));
}

void ASlAiHandApple::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex = 3;
}
