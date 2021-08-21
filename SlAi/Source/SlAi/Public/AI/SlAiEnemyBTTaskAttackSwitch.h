// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/SlAiEnemyBTTaskNodeBase.h"
#include "SlAiEnemyBTTaskAttackSwitch.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyBTTaskAttackSwitch : public USlAiEnemyBTTaskNodeBase
{
	GENERATED_BODY()

	//重写执行函数
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:

	UPROPERTY(EditAnywhere,Category="Blackborad")
	struct FBlackboardKeySelector AttactType;

	UPROPERTY(EditAnywhere,Category="Blackborad")
	struct FBlackboardKeySelector EnemyState;
};
