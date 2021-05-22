// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/SlAiPickUpStone.h"

ASlAiPickUpStone::ASlAiPickUpStone()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_StoneBlock_01.SM_Prop_StoneBlock_01'"));
	BaseMesh->SetStaticMesh(StaticMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.8f,0.8f,0.5f));
	ObjectIndex = 2;
}
