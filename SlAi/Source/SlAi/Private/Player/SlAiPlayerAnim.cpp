// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerAnim.h"

#include "Player/SlAiPlayerCharacter.h"

USlAiPlayerAnim::USlAiPlayerAnim()
{
	Speed = 0.0f;
	SpineRotator=FRotator(0.0f,0.0f,0.0f);
}

void USlAiPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	//初始化角色指针
	InitSPCharacter();
	//更新蓝图数据
	UpdateParameter();
}

void USlAiPlayerAnim::InitSPCharacter()
{
	if (!SPCharacter)SPCharacter=Cast<ASlAiPlayerCharacter>(TryGetPawnOwner());
}

void USlAiPlayerAnim::UpdateParameter()
{
	if (!SPCharacter)return;
	Speed = SPCharacter->GetVelocity().Size();
}
