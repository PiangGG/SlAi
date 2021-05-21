// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hand/SlAiHandObject.h"
#include "SlAiHandAxe.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API ASlAiHandAxe : public ASlAiHandObject
{
	GENERATED_BODY()

public:
	ASlAiHandAxe();
protected:
	virtual void BeginPlay() override;
	virtual void OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};


