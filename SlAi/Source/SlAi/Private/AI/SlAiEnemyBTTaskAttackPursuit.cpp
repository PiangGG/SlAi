// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskAttackPursuit.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskAttackPursuit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if(InitEnemyElement(OwnerComp))return EBTNodeResult::Failed;

	//播放追击动画
	float AttackDuration = SECharactor->PlayAttackAction(EEnemyAttackType::EA_Pursuit);
	//设置速度为600，不小于玩家
	SECharactor->SetMaxSpeed(600.0F);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsActionFinish.SelectedKeyName,false);
	//添加事件委托
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this,&USlAiEnemyBTTaskAttackPursuit::OnAnimationTimerDone);
	//注册到事件管理器
	SECharactor->GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimerDelegate,AttackDuration,false);

	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type USlAiEnemyBTTaskAttackPursuit::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功或者事件句柄没有激活，直接返回失败
	if (!InitEnemyElement(OwnerComp)||!TimerHandle.IsValid())return EBTNodeResult::Failed;
	//卸载时间委托
	SEController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	return EBTNodeResult::Aborted;
}

void USlAiEnemyBTTaskAttackPursuit::OnAnimationTimerDone()
{
	//设置动作完成
	if(SEController)SEController->ResetProcess(true);
	//修改速度回300
	if (SECharactor)SECharactor->SetMaxSpeed(300.0f);
}
