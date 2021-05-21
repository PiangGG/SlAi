// Fill out your copyright notice in the Description page of Project Settings.


#include "Hand/SlAiHandNone.h"

#include "Components/BoxComponent.h"

ASlAiHandNone::ASlAiHandNone()
{
	//不用绑定模型
	//设置碰撞体属性
	AffectCollision->SetBoxExtent(FVector(10.0f,10.0f,10.0f));
	AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,10.0f));
}

void ASlAiHandNone::BeginPlay()
{
	Super::BeginPlay();
	ObjectIndex = 0;
}
