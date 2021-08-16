// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SlAiEnemyBTTaskNodeBase.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiEnemyBTTaskNodeBase : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	//初始化控制器和角色,不成功就返回false
	bool InitEnemyElement(UBehaviorTreeComponent& OwnerComp);

protected:
	class ASlAiEnemyController* SEController;
	class ASlAiEnemyCharacter* SECharactor;
};
