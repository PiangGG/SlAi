// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlAiPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	USlAiPlayerAnim();
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=PlayAnim)
	float Speed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=PlayAnim)
	FRotator SpineRotator;
};
