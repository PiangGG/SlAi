// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/SlAIMenuGameMode.h"
#include "UI/HUD/SlAiMenuHUD.h"
#include "GamePlay/SlAiMenuController.h"

ASlAIMenuGameMode::ASlAIMenuGameMode()
{
	PlayerControllerClass = ASlAiMenuController::StaticClass();
	HUDClass = ASlAiMenuHUD::StaticClass();

}
