// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandHammer.h"

#include "Components/BoxComponent.h"

ASlAiHandHammer::ASlAiHandHammer()
{
	//给模型组件添加模型
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Bld_FencePost_01.SM_Bld_FencePost_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);
	BaseMesh->SetRelativeLocation(FVector(35.0f,0.0f,3.0f));
	BaseMesh->SetRelativeRotation(FRotator(0.0f,-90.0f,-90.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.4f,0.4f,0.4));
	
	ExtendMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtendMesh"));
	ExtendMesh->SetupAttachment(RootComponent);
	ExtendMesh->SetCollisionProfileName(FName("NoCollision"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticExtendMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'"));
	ExtendMesh->SetStaticMesh(StaticExtendMesh.Object);
	ExtendMesh->SetRelativeLocation(FVector(33.0f,1.0f,3.0f));
	ExtendMesh->SetRelativeRotation(FRotator(0.0f,-90.0f,-90.0f));
	ExtendMesh->SetRelativeScale3D(FVector(0.4f,0.4f,0.4));
	

	//设置碰撞体属性
	AffectCollision->SetRelativeLocation(FVector(26.0f,1.0f,3.0f));
	AffectCollision->SetRelativeScale3D(FVector(0.22f,0.44f,0.31f));
}

void ASlAiHandHammer::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex = 6;
}
