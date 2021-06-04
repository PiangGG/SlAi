// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTool/SlAiEnemyWeapon.h"

#include "Components/BoxComponent.h"

ASlAiEnemyWeapon::ASlAiEnemyWeapon()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticBaseMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Wep_GreatAxe_01.SM_Wep_GreatAxe_01'"));
	BaseMesh->SetStaticMesh(StaticBaseMesh.Object);

	BaseMesh->SetRelativeLocation(FVector(-38.0f,9.6f,9.8f));
	BaseMesh->SetRelativeRotation(FRotator(-10.f,76.5f,-99.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.75f));

	AffectCollision->SetRelativeLocation(FVector(0.0f,0.0f,158.0f));
	AffectCollision->SetRelativeScale3D(FVector(1.125f,0.22f,1.0f));
}
