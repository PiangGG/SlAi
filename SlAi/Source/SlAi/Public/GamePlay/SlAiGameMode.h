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
//注册MiniMap的贴图和材质
DECLARE_DELEGATE_OneParam(FRegisterMiniMap,class UTextureRenderTarget2D*)
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

	//初始化与更新小地图
	void InitializeMiniMapCamera();
public:
	class ASlAiPlayerController* SPController;
	class ASlAiPlayerCharacter* SPCharacter;
	class ASlAiPlayerState* SPState;

	FInitPackageManager InitPackageManager;

	FRegisterMiniMap RegisterMiniMap;
protected:
	virtual void BeginPlay() override;

	//初始化背包管理器
	void InitializePackage();  
private:
	//是否已经初始化背包
	bool IsInitPackage;

	//是否已经生成小地图
	bool IsCreateMiniMap;
	//小地图渲染相机指针
	class ASlAiSceneCapture2D* MiniMapCamera;
};
