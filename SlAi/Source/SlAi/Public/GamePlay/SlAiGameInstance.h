// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SlAiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API USlAiGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	//放一些初始化的东西|暂时用不着
	//virtual void Init() override;

	UPROPERTY(VisibleAnywhere,Category="SlAi")
	FString GameName;
};
