// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandStone.h"

#include "Components/BoxComponent.h"

ASlAiHandStone::ASlAiHandStone()
{
	//给模型组件添加模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeLocation(FVector(1.0f,-1.414f,7.071f));
	BaseMesh->SetRelativeRotation(FRotator(0.0f,0.0f,-135.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.25f,0.25f,0.25f));

	//设置碰撞体属性
	AffectCollision->SetBoxExtent(FVector(10.0f,10.0f,10.0f));
	AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,10.0f));
}

void ASlAiHandStone::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex = 2;
}
