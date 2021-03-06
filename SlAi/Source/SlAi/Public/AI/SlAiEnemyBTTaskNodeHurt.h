// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SlAiEnemyBTTaskNodeBase.h"
#include "SlAiEnemyBTTaskNodeHurt.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyBTTaskNodeHurt : public USlAiEnemyBTTaskNodeBase
{
	GENERATED_BODY()
	//重写执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	//重写任务终止函数
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	protected:

	//动作结束后事件
	void OnAnimationTimerDone();

	protected:

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector WaitTime;

	//攻击动作结束后的委托
	FTimerHandle TimerHandle;
};
