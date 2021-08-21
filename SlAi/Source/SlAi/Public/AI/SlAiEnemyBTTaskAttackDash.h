// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlAiEnemyBTTaskNodeBase.h"
#include "SlAiEnemyBTTaskAttackDash.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyBTTaskAttackDash : public USlAiEnemyBTTaskNodeBase
{
	GENERATED_BODY()

	//重写执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	//重写终止任务函数
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	//动作结束后事件
	void OnAnimationTimerDone();

protected:
	UPROPERTY(EditAnywhere,Category="Blackboard")
	struct FBlackboardKeySelector WaitTime;

	UPROPERTY(EditAnywhere,Category="Blackboard")
	struct FBlackboardKeySelector Destination;

	//攻击结束后的委托
	FTimerHandle TimerHandle;
};