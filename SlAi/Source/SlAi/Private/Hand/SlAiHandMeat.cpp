// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandMeat.h"

#include "Components/BoxComponent.h"

ASlAiHandMeat::ASlAiHandMeat()
{
	//给模型组件添加模型
    static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_Meat_02.SM_Prop_Meat_02'"));
    BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
    BaseMesh->SetRelativeLocation(FVector(6.0f,-7.044f,2.62f));
    BaseMesh->SetRelativeRotation(FRotator(-50.0f,90.0f,0.0f));
    BaseMesh->SetRelativeScale3D(FVector(0.75f,0.75f,0.75f));

    //设置碰撞体属性
    AffectCollision->SetBoxExtent(FVector(10.0f,10.0f,10.0f));
    AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,10.0f));
}

void ASlAiHandMeat::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex=4;
}
