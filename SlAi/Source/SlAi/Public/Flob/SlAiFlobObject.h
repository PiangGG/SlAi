// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/SlAiPlayerCharacter.h"

#include "SlAiFlobObject.generated.h"

UCLASS()
class SLAI_API ASlAiFlobObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiFlobObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//生成初始化
	void CreateFlobObject(int ObjectID);

	//丟棄物品初始化
	void ThrowFlobObject(int ObjectID,float DirYaw);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//渲染贴图
	void RenderTexture();
	//动态检测事件
	void DetectPlayer();
	//销毁事件
	void DestroyEvent();
private:
	class UBoxComponent* BoxCollison;
	class UStaticMeshComponent* BaseMesh;

	int ObjectIndex;

	class UTexture *ObjectIconTex;

	class UMaterialInstanceDynamic *ObjectIconDynamic;

	//玩家指针
	class ASlAiPlayerCharacter* SPCharacter;

	//动态检测Timer
	FTimerHandle DeterctTimer;

	//销毁Timer
	FTimerHandle DestroyTimer;
};
