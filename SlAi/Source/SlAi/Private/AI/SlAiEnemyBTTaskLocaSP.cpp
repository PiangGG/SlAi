// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskLocaSP.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskLocaSP::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如此初始化敌人参数不成功，直接返回失败
	if (!InitEnemyElement(OwnerComp))return  EBTNodeResult::Failed;
	//范围是20以内
	const float ChaseRadius = 20.0f;

	//获取玩家到敌人的单位向量
	FVector SPToSE = SEController->GetPlayerLocation()- SECharactor->GetActorLocation();
	SPToSE.Normalize();//归一化
	//探索起点是玩家位置减去与敌人之间的距离的一点点
	const FVector ChaseOrigin = SEController->GetPlayerLocation()- 100.0f*SPToSE;

	//保存随机位置
	FVector DesLoc(0.0f);

	//使用导航系统获取随机点
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController,ChaseOrigin,DesLoc,ChaseRadius);

	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName,DesLoc);

	SECharactor->SetMaxSpeed(300.0f);

	//返回成功
	return EBTNodeResult::Succeeded;
}
