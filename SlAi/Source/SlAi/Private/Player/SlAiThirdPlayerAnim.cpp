// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiThirdPlayerAnim.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SlAiPlayerCharacter.h"

USlAiThirdPlayerAnim::USlAiThirdPlayerAnim()
{
	
	IsInAir=false;
	Direction= 0.0f;
}

void USlAiThirdPlayerAnim::UpdateParameter()
{
	Super::UpdateParameter();
	if (!SPCharacter)return;
	//获取是否在跳跃
	IsInAir = SPCharacter->GetCharacterMovement()->IsFalling();
	//速度朝向的Yaw旋转减去Actor朝向其实就是摄像机朝向的Yaw旋转的得到的相对方向
	float PreDir = SPCharacter->GetVelocity().ToOrientationRotator().Yaw-SPCharacter->GetActorRotation().Yaw;
	//不清楚用点乘
	if (PreDir>180.0f)PreDir-=360.0f;
	if (PreDir<-180.0f)PreDir+=360.0f;
	Direction = PreDir;
}
