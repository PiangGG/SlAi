// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskChaseSwitch.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Data/SlAiTypes.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskChaseSwitch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如此初始化敌人参数不成功，直接返回失败
	if (!InitEnemyElement(OwnerComp))return  EBTNodeResult::Failed;
	//获取与玩家的距离
	float EPDistance = FVector::Distance(SECharactor->GetActorLocation(),SEController->GetPlayerLocation());

	//如果距离小于三百，设置状态为攻击，跳出追逐状态
	if (EPDistance<300.0F)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName,(uint8)EEnemyAIState::ES_Attack);
		return EBTNodeResult::Failed;
	}

	//如果距离大于1500了，跳到巡逻状态，并设置没有锁定玩家
	if(EPDistance>1500.0F)
	{
		//告诉控制器丢失了玩家
		SEController->LoosePlayer();
		//修改状态为巡逻
		OwnerComp.GetBlackboardComponent()->SetValueAsEnum(EnemyState.SelectedKeyName,(uint8)EEnemyAIState::ES_Patrol);
		//跳出追逐状态
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Succeeded;
	
}
