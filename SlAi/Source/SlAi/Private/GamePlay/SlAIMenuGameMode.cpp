// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/SlAIMenuGameMode.h"

#include "GamePlay/SlAiGameInstance.h"
#include "UI/HUD/SlAiMenuHUD.h"
#include "GamePlay/SlAiMenuController.h"
#include "Kismet/GameplayStatics.h"

ASlAIMenuGameMode::ASlAIMenuGameMode()
{
	PlayerControllerClass = ASlAiMenuController::StaticClass();
	HUDClass = ASlAiMenuHUD::StaticClass();

}

void ASlAIMenuGameMode::BeginPlay()
{
	Cast<USlAiGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GameName = FString("SlAi");
	
}
