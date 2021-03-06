// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SlAiTypes.h"
#include "GameFramework/Character.h"
#include "SlAiPlayerCharacter.generated.h"

UCLASS()
class SLAI_API ASlAiPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlAiPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//修改视角
	void ChangeView(EGameViewMode::Type NewGameView);
	//修改当前的手持物品
	void ChangeHandObject(TSubclassOf<class AActor> HandObjectClass);
	//修改手持物品碰撞检测是否开启
	void ChangeHandObjectDetect(bool IsOpen);
	//是否渲染手上物品
	void RenderHandObject(bool IsRender);
	//丟棄物品
	void PlayerThrowObject(int ObjectID,int Num);
	//背包是否有空间
	bool IsPackageFree(int ObjectID);
	//添加物品到背包
	void AddPackageObject(int ObjectID);
	//吃完东西调用事件，由Anim进行调用
	void EatUpEvent();
	//获取是否已经死亡
	bool IsPlayerDead();
	//接受伤害
	void AcceptDamage(int Damage);

	//获取摄像机位置
	FVector GetCameraPos();
public:
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class UCameraComponent* ThirdCamera;
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class UCameraComponent* FirstCamera;
	//玩家控制器指针
	class ASlAiPlayerController *SPController;
	//当前视角模式
	EGameViewMode::Type GameView;

	//上半身动画状态
	EUpperBody::Type upperType;
	//是否允许切换视角
	bool IsAllowSwitch;

	//是否锁住输入
	bool IsInputLocaked;

	bool IsAttack;
private:
	void MoveForward(float value);
	void MoveRight(float value);
	void LookUpAtRate(float value);
	void Turn(float value);
	void TurnAtRoate(float value);
	void OnStartJump();
	void OnStopJump();
	void OnStartRun();
	void OnStopRun();
private:
	//第一人称骨骼模型
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	USkeletalMeshComponent* MeshFirst;

	//手上物品
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class UChildActorComponent* HandObject;
	//旋转比例
	float BaseLookUpRate;
	float BaseTurnRate;

	
};
