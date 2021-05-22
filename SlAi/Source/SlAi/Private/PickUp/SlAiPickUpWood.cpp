// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp/SlAiPickUpWood.h"

ASlAiPickUpWood::ASlAiPickUpWood()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/Res/PolygonAdventure/Meshes/SM_Prop_Loghalf_01.SM_Prop_Loghalf_01'"));
	BaseMesh->SetStaticMesh(StaticMesh.Object);

	BaseMesh->SetRelativeScale3D(FVector(0.8f,0.8f,0.5f));
	ObjectIndex = 1;
}
