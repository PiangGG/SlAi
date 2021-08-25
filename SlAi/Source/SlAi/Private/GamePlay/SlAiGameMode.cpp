// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/SlAiGameMode.h"

#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "GamePlay/SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SlAiPackageManager.h"
#include "Player/SlAiPlayerCharacter.h"
#include "Player/SlAiPlayerController.h"
#include "Player/SlAiPlayerState.h"
#include "UI/HUD/SlAiGameHUD.h"

ASlAiGameMode::ASlAiGameMode()
{
	//允许开启Tick函数
	PrimaryActorTick.bCanEverTick=true;
	//添加组件
	HUDClass=ASlAiGameHUD::StaticClass();
	PlayerControllerClass=ASlAiPlayerController::StaticClass();
	DefaultPawnClass = ASlAiPlayerCharacter::StaticClass();
	PlayerStateClass = ASlAiPlayerState::StaticClass();

	IsInitPackage=false;
	
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{
	//Super()
	InitializePackage();
}

void ASlAiGameMode::InitGamePlayModule()
{
	//添加引用
	SPController=Cast<ASlAiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	SPCharacter=Cast<ASlAiPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	if (SPController->PlayerState&&SPController)
	{
		SPState=Cast<ASlAiPlayerState>(SPController->PlayerState);
	}
}

void ASlAiGameMode::BeginPlay()
{
	//初始化游戏数据
	//初始化游戏数据
	SlAiDataHandle::Get()->InitializeGameData();
	if (!SPController)	InitGamePlayModule();
	
}

void ASlAiGameMode::InitializePackage()
{
	if (IsInitPackage)return;
	InitPackageManager.ExecuteIfBound();
	//綁定丟棄物品委托
	SlAiPackageManager::Get()->PlayerThrowObject.BindUObject(SPCharacter,&ASlAiPlayerCharacter::PlayerThrowObject);
	//綁定修改快捷欄信息
	SlAiPackageManager::Get()->ChangeHandObject.BindUObject(SPState,&ASlAiPlayerState::ChangeHandObject);
	
	IsInitPackage=true;
	
}
