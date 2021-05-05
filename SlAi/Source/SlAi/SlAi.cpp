// Copyright Epic Games, Inc. All Rights Reserved.

#include "SlAi.h"
#include "Modules/ModuleManager.h"
#include "Styling/SlateStyleRegistry.h"
#include "UI/Style/SlAiStyle.h"


void FSlAiModule::StartupModule()
{
	//初始化样式
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiStyle::GetStyleSetName());
	SlAiStyle::Initialze();
}

void FSlAiModule::ShutdownModule()
{
	SlAiStyle::ShutDown();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FSlAiModule, SlAi, "SlAi");