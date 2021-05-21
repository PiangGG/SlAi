// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandObject.h"

#include "Components/BoxComponent.h"

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
	OverlayBegin.BindUFunction(this,"OnOverlayEnd");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayEnd);
}

// Called when the game starts or when spawned
void ASlAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlAiHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASlAiHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ASlAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

