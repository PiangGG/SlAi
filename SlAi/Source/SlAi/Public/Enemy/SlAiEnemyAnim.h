// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlAiEnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	USlAiEnemyAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=EnemyAnim)
	float Speed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=EnemyAnim)
	float IdleType;

	protected: 
	class ASlAiEnemyCharacter *SECharacter;
};