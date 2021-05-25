// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//渲染贴图
	void RenderTexture();  
private:
	class UBoxComponent* BoxCollison;
	class UStaticMeshComponent* BaseMesh;

	int ObjectIndex;

	class UTexture *ObjectIconTex;

	class UMaterialInstanceDynamic *ObjectIconDynamic;

};
