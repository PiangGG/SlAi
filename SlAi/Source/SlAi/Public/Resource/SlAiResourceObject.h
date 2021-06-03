// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "GameFramework/Actor.h"
#include "SlAiResourceObject.generated.h"

UCLASS()
class SLAI_API ASlAiResourceObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiResourceObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//获取物品信息
	FText GetInfoText()const;
	//获取资源类型
	EResourceType::Type	GetResourceType();

	//获取血量百分比
	float GetHPRange();

	//获取伤害
	ASlAiResourceObject* TakeObjectDamage(int Damge);
	
	virtual int GetResourceIndex();
public:
	//资源ID
	int ResourceIndex=0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//生成掉落物
	void CreateFlobObject();
protected:
	//根组件
	USceneComponent * RootScene;
	//静态模型
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=SlAi)
	UStaticMeshComponent* BaseMesh; 
	//保存地址资源，用于随机刷资源
	TArray<FString> ResourcePath;
	//血量
	int HP;
	//基础血量
	int BaseHP;
};
