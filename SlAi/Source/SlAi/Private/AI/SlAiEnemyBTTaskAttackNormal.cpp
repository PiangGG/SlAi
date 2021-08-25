// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskAttackNormal.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskAttackNormal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功，直接返回失败
	if (!InitEnemyElement(OwnerComp))return EBTNodeResult::Failed;
	//播放普通攻击动画
	float AttackDuration  = SECharactor->PlayAttackAction(EEnemyAttackType::EA_Normal);
	//设置参数
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName,AttackDuration);
	return  EBTNodeResult::Succeeded;
}
