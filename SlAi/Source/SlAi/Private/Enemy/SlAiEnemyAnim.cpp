// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SlAiEnemyAnim.h"

#include "Enemy/SlAiEnemyCharacter.h"

USlAiEnemyAnim::USlAiEnemyAnim()
{
	//初始化参数
	Speed = 0.0f;
	IdleType = 0.0f;
}

void USlAiEnemyAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	//初始化角色指针
	if (!SECharacter)SECharacter = Cast<ASlAiEnemyCharacter>(TryGetPawnOwner());
	if (!SECharacter)return;

	//设置速度
	Speed=SECharacter->GetVelocity().Size();
}
