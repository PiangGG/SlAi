// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SlAiGameMode.generated.h"

/**
 * 
 */
//初始化背包管理类委托
DECLARE_DELEGATE(FInitPackageManager)
UCLASS()
class SLAI_API ASlAiGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASlAiGameMode();

	//重写帧函数
	virtual void Tick(float DeltaSeconds) override;
	//组件赋值，给GameHUD调用,避免空引用引起崩溃
	void InitGamePlayModule();
public:
	class ASlAiPlayerController* SPController;
	class ASlAiPlayerCharacter* SPCharacter;
	class ASlAiPlayerState* SPState;

	FInitPackageManager InitPackageManager;
protected:
	virtual void BeginPlay() override;

	//初始化背包管理器
	void InitializePackage();  
private:
	//是否已经初始化背包
	bool IsInitPackage;
};
