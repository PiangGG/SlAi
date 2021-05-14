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
	//存档数据
	TArray<FString> RecordDataList;

	//存档名
	FString RecordName;
private:
	static TSharedPtr<SlAiDataHandle> Create();

	//根据enum类型获取字符串
	template<typename TEnum>
	FString GetEnumValueAsString(const FString &Name,TEnum value);
	//根据字符串获取TENum的值
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name,FString Value );
	//初始化存档数据
	void InitRecordData();
private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
};
