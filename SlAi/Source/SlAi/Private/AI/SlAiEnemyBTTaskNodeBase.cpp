// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskNodeBase.h"

#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

bool USlAiEnemyBTTaskNodeBase::InitEnemyElement(UBehaviorTreeComponent& OwnerComp)
{
	//如果已经初始化,直接return，避免重复调用
	if(SEController &&SECharactor) return  true;

	//不存在，就进行赋值
	SEController = Cast<ASlAiEnemyController>(OwnerComp.GetAIOwner());
	if (SEController)
	{
		SECharactor = Cast<ASlAiEnemyCharacter>(SEController->GetPawn());
		if (SECharactor)return true;
	}
	return false;
	
}
