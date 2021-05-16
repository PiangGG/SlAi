// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/SlAiGameMode.h"

#include "Common/SlAiHelper.h"
#include "Data/SlAiDataHandle.h"
#include "GamePlay/SlAiGameInstance.h"
#include "Kismet/GameplayStatics.h"
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
	
}

void ASlAiGameMode::Tick(float DeltaSeconds)
{
	//Super()
}

void ASlAiGameMode::BeginPlay()
{
	SlAiHelper::Debug(FString("DataHnadle:"+SlAiDataHandle::Get()->RecordName,30));
	SlAiHelper::Debug(FString("GameInstance:"+Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName,30));
}
