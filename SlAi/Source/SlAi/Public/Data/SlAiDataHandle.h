// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SlAiTypes.h"

/**
 * 
 */
class SLAI_API SlAiDataHandle
{
public:
	SlAiDataHandle();
	static void Initialize();
	static TSharedPtr<SlAiDataHandle> Get();
	//修改中英文
	void ChangeLocalizationCultrue(ECultrueTeam Cultrue);
public:
	ECultrueTeam CurrentCultrueTeam;
private:
	static TSharedPtr<SlAiDataHandle> Create();
private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
};
