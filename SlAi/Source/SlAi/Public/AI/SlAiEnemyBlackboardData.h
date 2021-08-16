// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardData.h"
#include "SlAiEnemyBlackboardData.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyBlackboardData : public UBlackboardData
{
	GENERATED_BODY()

	public:
	virtual void PostLoad() override;
};
