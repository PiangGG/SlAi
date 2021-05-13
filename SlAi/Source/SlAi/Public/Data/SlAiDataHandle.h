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
	void ChangeLocalizationCulture(ECultureTeam Cultrue);
	//修改菜单音量
	void ResetMenuVolume(float Musicval,float Soundvalue);
public:
	//语言
	ECultureTeam CurrentCultrueTeam;
	//音量|音乐
	float MusicVolume;
	float SoundVolume;
private:
	static TSharedPtr<SlAiDataHandle> Create();
private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
};
