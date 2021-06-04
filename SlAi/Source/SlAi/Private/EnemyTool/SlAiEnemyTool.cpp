// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTool/SlAiEnemyTool.h"

#include "Components/BoxComponent.h"
#include "EnemyTool/SlAiEnemySheild.h"
#include "EnemyTool/SlAiEnemyWeapon.h"

// Sets default values
ASlAiEnemyTool::ASlAiEnemyTool()
{
 	//实例化根节点
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent=RootScene;

	//在这里实例化模型组件但是不进行模型绑定
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	//实现碰撞组件
	AffectCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectCollision->SetupAttachment(BaseMesh);
	AffectCollision->SetCollisionProfileName(FName("EnemyToolProfile"));
	//初始时关闭Overlay检测
	AffectCollision->SetGenerateOverlapEvents(false);

	//绑定检测方法到碰撞体
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this,"OnOverlayBegin");
	AffectCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayBegin.BindUFunction(this,"OnOverlayEnd");
	AffectCollision->OnComponentEndOverlap.Add(OverlayEnd);
}

void ASlAiEnemyTool::ChangeOverlayDetect(bool IsOpen)
{
	AffectCollision->SetGenerateOverlapEvents(true);
}

TSubclassOf<AActor> ASlAiEnemyTool::SpawnEnemyWeapon()
{
	return ASlAiEnemyWeapon::StaticClass();
}

TSubclassOf<AActor> ASlAiEnemyTool::SpawnEnemyShild()
{
	return ASlAiEnemySheild::StaticClass();
}

void ASlAiEnemyTool::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASlAiEnemyTool::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
