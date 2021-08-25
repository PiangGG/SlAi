// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskAttackSwitch.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskAttackSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功，直接返回失败
	if (!InitEnemyElement(OwnerComp))return EBTNodeResult::Failed;

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(PlayerPawn.SelectedKeyName,SEController->GetPlayerPawn());
	//判断玩家是否死亡
	if (SEController->IsPlayerDead())
	{
		//告诉控制器，丢失玩家
		SEController->LoosePlayer();
		//修改状态为巡逻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName,(uint8)EEnemyAIState::ES_Patrol);
		//跳出攻击状态
		return EBTNodeResult::Failed;
	}
	//如果距离小于200
	//获取与玩家的距离
	float EPDistance = FVector::Distance(SECharactor->GetActorLocation(),SEController->GetPlayerLocation());

	if (EPDistance<200)
	{
		//修改状态为普攻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttactType.SelectedKeyName,(uint8)EEnemyAttackType::EA_Normal);
		return EBTNodeResult::Succeeded;
	}
	//如果大于300
	if (EPDistance>=200&&EPDistance<300)
	{
		//修改状态为普攻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AttactType.SelectedKeyName,(uint8)EEnemyAttackType::EA_Dash);
		return EBTNodeResult::Succeeded;	
	}
	if (EPDistance>300)
	{
		//修改状态为追逐
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName,(uint8)EEnemyAIState::ES_Chase);
		//跳出攻击状态
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;
}
