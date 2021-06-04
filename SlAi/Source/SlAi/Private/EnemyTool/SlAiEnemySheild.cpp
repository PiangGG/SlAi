// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTool/SlAiEnemySheild.h"

#include "Components/BoxComponent.h"

ASlAiEnemySheild::ASlAiEnemySheild()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_Sheild_01.SM_Wep_Sheild_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(53.0f,-3.0f,-9.0f));
	BaseMesh->SetRelativeRotation(FRotator(0.0f,90.0f,90.0f));

	AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,43.0f));
	AffectCollision->SetRelativeScale3D(FVector(0.8125f,0.156f,1.344f));
}
