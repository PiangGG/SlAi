// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerAnim.h"

#include "Common/SlAiHelper.h"
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
	//更新Montage
	UpdateMontage();
}

void USlAiPlayerAnim::ChangeDetection(bool IsOpen)
{
	if (!SPCharacter)return;
	SPCharacter->ChangeHandObjectDetect(IsOpen);
}

void USlAiPlayerAnim::RenderHandObject(bool isRender)
{
	if (!SPCharacter)return;
	SPCharacter->RenderHandObject(isRender);
}

void USlAiPlayerAnim::InitSPCharacter()
{
	if (!SPCharacter)SPCharacter=Cast<ASlAiPlayerCharacter>(TryGetPawnOwner());
}

void USlAiPlayerAnim::UpdateParameter()
{
	if (!SPCharacter)return;
	Speed = SPCharacter->GetVelocity().Size();
	float SpineDir=SPCharacter->GetActorRotation().Yaw-90;
	if (SpineDir>180.0f)SpineDir-=360.0f;
	if (SpineDir<180.0f)SpineDir+=360.0f;
	SpineRotator = FRotator(0.0f,SpineDir,90.f);
}

void USlAiPlayerAnim::UpdateMontage()
{
	if (!SPCharacter)return;
	//如果当前的人称状态和这个动作不一致，直接返回
	if(SPCharacter->GameView!=GameView)return;
	//如果当前蒙太奇没播放完，不更新动作
	if (!Montage_GetIsStopped(CurrentMontage))return;
	switch (SPCharacter->upperType) {
	case EUpperBody::None:
		//如果有动作播放，停止
		if (CurrentMontage!=nullptr)
		{
			Montage_Stop(0);
			CurrentMontage=nullptr;
			AllowViewChange(true);
		}
		break;
	case EUpperBody::Punch:
		if (!Montage_IsPlaying(PlayerPunchMontage))
		{
			Montage_Play(PlayerPunchMontage);
			CurrentMontage=PlayerPunchMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Hit:
		if (!Montage_IsPlaying(PlayerHitMentage))
		{
			Montage_Play(PlayerHitMentage);
			CurrentMontage=PlayerHitMentage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Fight:
		if (!Montage_IsPlaying(PlayerFightMontage))
		{
			Montage_Play(PlayerFightMontage);
			CurrentMontage=PlayerFightMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::PickUp:
		if (!Montage_IsPlaying(PlayerPickUpMontage))
		{
			Montage_Play(PlayerPickUpMontage);
			CurrentMontage=PlayerPickUpMontage;
			AllowViewChange(false);
		}
		break;
	case EUpperBody::Eat:
		if (!Montage_IsPlaying(PlayerEatMontage))
		{
			Montage_Play(PlayerEatMontage);
			CurrentMontage=PlayerEatMontage;
			AllowViewChange(false);
		}
		break;
	}
}

void USlAiPlayerAnim::AllowViewChange(bool IsAllow)
{
	if (!SPCharacter)return;
	SPCharacter->IsAllowSwitch = IsAllow;	
		
}
