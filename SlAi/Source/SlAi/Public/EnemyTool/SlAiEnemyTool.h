// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiEnemyTool.generated.h"

UCLASS()
class SLAI_API ASlAiEnemyTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiEnemyTool();

	//是否允许检测
	void ChangeOverlayDetect(bool IsOpen);
	//根据物品ID返回物品的工厂方法
	static TSubclassOf<AActor> SpawnEnemyWeapon();
	static TSubclassOf<AActor> SpawnEnemyShild();
protected:
	UFUNCTION()
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent*
			OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void OnOverlayEnd(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent*
		OtherComp,int32 OtherBodyIndex);
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
