// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlAiGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API ASlAiGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	ASlAiGameHUD();
private:
	TSharedPtr<class SSlAiGameHUDWidget> GameHUDWidget;	
};
