// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandSword.h"

#include "Components/BoxComponent.h"

ASlAiHandSword::ASlAiHandSword()
{
	//给模型组件添加模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Sword_01.SM_Wep_Sword_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeLocation(FVector(-15.0f,1.0f,2.0f));
	BaseMesh->SetRelativeRotation(FRotator(-20.0f,90.0f,-90.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.8f,0.8f,1.0f));

	//设置碰撞体属性
	AffectCollision->SetRelativeLocation(FVector(62.0f,1.0f,2.0f));
	AffectCollision->SetRelativeRotation(FRotator(0.0f,0.0f,20.0f));
	AffectCollision->SetRelativeScale3D(FVector(1.5f,0.19f,0.1f));
}

void ASlAiHandSword::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex = 7;
}
