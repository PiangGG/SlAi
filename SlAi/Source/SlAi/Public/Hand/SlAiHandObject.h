// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiHandObject.generated.h"

UCLASS()
class SLAI_API ASlAiHandObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiHandObject();
	//根据物品ID返回物品的工厂方法
	static TSubclassOf<AActor> SpawnHandObject(int ObjectID);
public:
	int ObjectIndex;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent*
		OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent*
		OtherComp,int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	//根组件
	class USceneComponent* RootScene;
	//网格体
	UPROPERTY(EditAnywhere,Category=SlAi)
 	class UStaticMeshComponent* BaseMesh;
	//盒子碰撞体
	UPROPERTY(EditAnywhere,Category=SlAi)
	class UBoxComponent* AffectCollision;
};
