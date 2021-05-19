// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SlAiGameHUD.h"

#include "UI/Widget/SSlAiGameHUDWidget.h"
#include "Widgets/SWeakWidget.h"

ASlAiGameHUD::ASlAiGameHUD()
{
	if (GEngine&&GEngine->GameViewport)
	{
		SAssignNew(GameHUDWidget,SSlAiGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));
	}
}
