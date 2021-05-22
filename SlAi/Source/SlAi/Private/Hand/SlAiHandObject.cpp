// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandObject.h"

#include "Common/SlAiHelper.h"
#include "Components/BoxComponent.h"
#include "Hand/SlAiHandApple.h"
#include "Hand/SlAiHandAxe.h"
#include "Hand/SlAiHandHammer.h"
#include "Hand/SlAiHandMeat.h"
#include "Hand/SlAiHandNone.h"
#include "Hand/SlAiHandStone.h"
#include "Hand/SlAiHandSword.h"
#include "Hand/SlAiHandWood.h"

// Sets default values
ASlAiHandObject::ASlAiHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//BaseMesh->SetStaticMesh(StaticMesh.Object);
	//ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Sword_01.SM_Wep_Sword_01'"));
	RootScene=CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent=RootScene;
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));
	//实例化碰撞组件
	AffectCollision=CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(RootComponent);
	AffectCollision->SetCollisionProfileName(FName("ToolProfile"));

	//初始时关闭Overlay检测
	AffectCollision->SetGenerateOverlapEvents(false);

	//绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this,"OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this,"OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);
}

TSubclassOf<AActor> ASlAiHandObject::SpawnHandObject(int ObjectID)
{
	switch (ObjectID)
	{
		case 0:
			return ASlAiHandNone::StaticClass();
		case 1:
			return ASlAiHandWood::StaticClass();
		case 2:
			return ASlAiHandStone::StaticClass();
		case 3:
			return ASlAiHandApple::StaticClass();
		case 4:
			return ASlAiHandMeat::StaticClass();
		case 5:
			return ASlAiHandAxe::StaticClass();
		case 6:
			return ASlAiHandHammer::StaticClass();
		case 7:
			return ASlAiHandSword::StaticClass();
		default:
			return ASlAiHandNone::StaticClass();
	}
}

void ASlAiHandObject::ChangeOverlayDetect(bool IsOpen)
{
	AffectCollision->SetGenerateOverlapEvents(IsOpen);
}

// Called when the game starts or when spawned
void ASlAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlAiHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SlAiHelper::Debug(FString("OnOverlayBegin"));
}

void ASlAiHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SlAiHelper::Debug(FString("OnOverlayEnd"));
}

// Called every frame
void ASlAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

