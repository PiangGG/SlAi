// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskAttackDash.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskAttackDash::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功，直接返回失败
	if (!InitEnemyElement(OwnerComp))return EBTNodeResult::Failed;

	//播放冲刺动画，且获取动画时长
	float AttackDuration = SECharactor->PlayAttackAction(EEnemyAttackType::EA_Dash);

	//范围是0
	const float ChaseRadius = 5.0f;
	//获取玩家到敌人的单位向量
	FVector SPToSE = SEController->GetPlayerLocation() - SECharactor->GetActorLocation();

	SPToSE.Normalize();
	//探索起点是玩家位置减去与敌人之间的距离的一点点
	const FVector ChaseOrigin = SEController->GetPlayerLocation()-20*SPToSE;
	
	//保存随机位置
	FVector DesLoc(0.0f);

	//使用导航系统获取随机点
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SECharactor,ChaseOrigin,DesLoc,ChaseRadius);

	//角色速度
	float Speed  = (FVector::Distance(SEController->GetPlayerLocation(),DesLoc))/AttackDuration+30.0f;

	//修改敌人的速度
	SECharactor->SetMaxSpeed(Speed);

	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName,DesLoc);
	//设置参数
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName,AttackDuration);
	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this,&USlAiEnemyBTTaskAttackDash::OnAnimationTimerDone);
	//注册到事件管理器
	SEController->GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate,AttackDuration,false);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type USlAiEnemyBTTaskAttackDash::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功或者事件句柄没有激活，直接返回失败
	if (!InitEnemyElement(OwnerComp)||!TimerHandle.IsValid())return EBTNodeResult::Failed;
	//卸载时间委托
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle)

	return EBTNodeResult::Aborted;
}

void USlAiEnemyBTTaskAttackDash::OnAnimationTimerDone()
{
	//重新设置时间为300
	if (SECharactor)SECharactor->SetMaxSpeed(300.0f);
}
