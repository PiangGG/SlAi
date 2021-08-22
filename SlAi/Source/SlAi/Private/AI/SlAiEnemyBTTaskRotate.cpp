// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SlAiEnemyBTTaskRotate.h"

#include "Enemy/SlAiEnemyCharacter.h"
#include "Enemy/SlAiEnemyController.h"

EBTNodeResult::Type USlAiEnemyBTTaskRotate::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//如果初始化敌人参数不成功,直接返回失败
	if (!InitEnemyElement(OwnerComp)) return EBTNodeResult::Failed;

	//获取玩家到敌人的向量，除去Y向量
	FVector SEToSP = FVector(SEController->GetPlayerLocation().X,SEController->GetPlayerLocation().Y,0)
	-FVector(SECharactor->GetActorLocation().X,SECharactor->GetActorLocation().Y,0.0f);
	SEToSP.Normalize();
	//告诉敌人新的朝向
	SECharactor->UpdateRotatation(FRotationMatrix::MakeFromX(SEToSP).Rotator());
	return EBTNodeResult::Succeeded;
}
