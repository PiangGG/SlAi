// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "SlAIBTDecoratorBase.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAIBTDecoratorBase : public UBTDecorator
{
	GENERATED_BODY()
	//判定节点要不要运行
	//对应蓝图节点的PerformConditioncheck;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
