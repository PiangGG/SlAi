// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskNodeEscapeSwitch.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskNodeEscapeSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;
	//获取与玩家的距离
	float EPDistance = FVector::Distance(SECharactor->GetActorLocation(), SEController->GetPlayerLocation());
	//如果大于1500了,回到巡逻状态,并且设置没有锁定玩家
	if (EPDistance > 1500.f) {
		//告诉控制器丢失了玩家
		SEController->LoosePlayer();
		//修改状态为巡逻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName, (uint8)EEnemyAIState::ES_Patrol);
	}
	return EBTNodeResult::Succeeded;
}
