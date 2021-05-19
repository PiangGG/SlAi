// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SlAiTypes.h"
#include "Sound/SoundCue.h"

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
	//游戏数据初始化
	void InitialzeGameData();
	//初始化物品属性
	void InitObjectAttr();
	//物品贴图资源数组
	TArray<const FSlateBrush*> ObjectBrushList;
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
	//物品属性
	TMap<int,TSharedPtr<ObjectAttribute>> ObjectAttrMap;
	
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
	//初始化Menu声音数据
	void InitializedMenuAudio();
private:
	static TSharedPtr<SlAiDataHandle> DataInstance;
	//保存Menu的声音
	TMap<FString,TArray<USoundCue*>> MenuAudioResource;

	//获取MenuStyle
	const struct FSlAiMenuStyle *MenuStyle;
	//获取GameStyle
	const struct FSlAiGameStyle *GameStyle;
};
