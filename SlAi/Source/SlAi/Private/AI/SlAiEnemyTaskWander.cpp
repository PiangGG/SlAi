// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyTaskWander.h"

#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type USlAiEnemyTaskWander::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp))return EBTNodeResult::Failed;

	//溜达的范围是1000
	const float WanderRadius = 1000.0f;

	//溜达点是自己的起始位置
	const FVector WanderOrigin = SECharactor->GetActorLocation();

	//DrawDebugSphere(GetWorld(),WanderOrigin,50,10,FColor::Blue);
	//获取随机位置
	FVector DesLoc(0.0f);
	//使用导航系统获取随机点
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController,WanderOrigin,DesLoc,WanderRadius);

	while (FVector::Distance(WanderOrigin,DesLoc)<500.0f)
	{
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(SEController,WanderOrigin,DesLoc,WanderRadius);
	}
	//修改速度为100
	SECharactor->SetMaxSpeed(100.0f);
	//修改目的地
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Destination.SelectedKeyName,DesLoc);
	//获取停顿时长
	float TotalWaitTime = SECharactor->GetIdleWaitTime();
	//修改等待时长
	OwnerComp.GetBlackboardComponent()->SetValueAsFloat(WaitTime.SelectedKeyName,TotalWaitTime);
	//返回成功
	return EBTNodeResult::Succeeded;
}
