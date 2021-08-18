// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SlAiEnemyBTTaskNodeBase.h"
#include "SlAiEnemyBTTaskChaseSwitch.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyBTTaskChaseSwitch : public USlAiEnemyBTTaskNodeBase
{
	GENERATED_BODY()

	//重写执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	protected:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	struct FBlackboardKeySelector EnemyState;
};
