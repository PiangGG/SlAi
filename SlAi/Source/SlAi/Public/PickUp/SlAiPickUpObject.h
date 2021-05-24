// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlAiPickUpObject.generated.h"

UCLASS()
class SLAI_API ASlAiPickUpObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlAiPickUpObject();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//获取物品信息
	FText GetInfoText()const;

	//被拾取，返回物品ID
	int TakePickUp();
public:
	int ObjectIndex;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:	
	//根组件
	USceneComponent * RootScene;
	//静态模型
	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=SlAi)
	UStaticMeshComponent* BaseMesh; 

};
