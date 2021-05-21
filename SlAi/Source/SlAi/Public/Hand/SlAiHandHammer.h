// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandHammer.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API ASlAiHandHammer : public ASlAiHandObject
{
	GENERATED_BODY()
	public:
	ASlAiHandHammer();
	protected:
	virtual void BeginPlay() override;

	protected:
	UStaticMeshComponent* ExtendMesh;
};
