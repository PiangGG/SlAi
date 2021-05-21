// Fill out your copyright notice in the Description page of Project Settings.

#include "Hand/SlAiHandAxe.h"
#include "Components/BoxComponent.h"

ASlAiHandAxe::ASlAiHandAxe()
{
	//给模型组件添加模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Axe_01.SM_Wep_Axe_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeLocation(FVector(-28.0f,-4.9f,3.23f));
	BaseMesh->SetRelativeRotation(FRotator(0.0f,-90.0f,90.0f));
	BaseMesh->SetRelativeScale3D(FVector(1.0f,1.0f,1.0f));

	//设置碰撞体属性
	AffectCollision->SetRelativeLocation(FVector(32.0f,-5.0f,3.0f));
	AffectCollision->SetRelativeScale3D(FVector(0.375f,0.5f,0.135f));
}

void ASlAiHandAxe::BeginPlay()
{
	Super::BeginPlay();
	//定义物品序号
	ObjectIndex=5; 
}

void ASlAiHandAxe::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
