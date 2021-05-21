// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandWood.h"

#include "Components/BoxComponent.h"

ASlAiHandWood::ASlAiHandWood()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Env_TreeLog_01.SM_Env_TreeLog_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	//BaseMesh->SetRelativeLocation(FVector(1.0f,-1.414f,7.071f));
	BaseMesh->SetRelativeRotation(FRotator(0.0f,-20.0f,0.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));

	//设置碰撞体属性
	AffectCollision->SetBoxExtent(FVector(10.0f,10.0f,10.0f));
	AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,10.0f));
}

void ASlAiHandWood::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex = 1;
}
