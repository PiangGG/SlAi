// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Data/SlAiTypes.h"

#include "SlAiPlayerAnim.generated.h"

/**
 * 
 */
class UAnimMontage;
UCLASS()
class SLAI_API USlAiPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	USlAiPlayerAnim();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=PlayAnim)
	float Speed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=PlayAnim)
	FRotator SpineRotator;
protected:
	//获取角色指针
	void InitSPCharacter();
	//更新属性
	virtual  void UpdateParameter();
	//更新动作
	virtual void UpdateMontage();
	//修改是否允许切换视角
	void AllowViewChange(bool IsAllow);
protected:
	//
	class ASlAiPlayerCharacter* SPCharacter;
	//上半身的蒙太奇
	UAnimMontage* PlayerHitMentage;
	UAnimMontage* PlayerFightMontage;
	UAnimMontage* PlayerPunchMontage;
	UAnimMontage* PlayerEatMontage;
	UAnimMontage* PlayerPickUpMontage;

	//保存当前播放的Montage
	UAnimMontage* CurrentMontage;
	//指定自己的运行人称
	EGameViewMode::Type GameView;
};
