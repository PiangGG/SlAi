// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiDataHandle.h"

#include "Common/SlAiHelper.h"
#include "Data/SlAiJsonHandle.h"
#include "Data/SlAiSingleton.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAiMenuWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"

TSharedPtr<SlAiDataHandle> SlAiDataHandle::DataInstance=NULL;

void SlAiDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance=SlAiDataHandle::Create();
	}
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

TSharedPtr<SlAiDataHandle> SlAiDataHandle::Create()
{
	//MakeShareable 可以用来创建共享指针和共享引用
	TSharedPtr<SlAiDataHandle> DataRef = MakeShareable(new SlAiDataHandle());
	return DataRef;
}

void SlAiDataHandle::InitRecordData()
{
	//初始化存档名
	RecordName=FString("");
	//获取语言
	FString Culture;
	//读取存档数据
	SlAiSingleton<SlAiJsonHandle>::Get()->RecordDataJsonRead(Culture,MusicVolume,SoundVolume,RecordDataList);
	
	//初始化语言
	ChangeLocalizationCulture(GetEnumValueFromString<ECultureTeam>(FString("ECultureTeam"),Culture));

	//初始化声音
	//ResetMenuVolume(MusicVolume,SoundVolume);
	//循环读取RecordDataList
	for (TArray<FString>::TIterator It(RecordDataList);It;++It)
	{
		
	}
}

void SlAiDataHandle::InitializedMenuAudio()
{
	//获取MenuStyle
	MenuStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiMenuStyle>("BPSlAiMenuStyle");

	//添加资源文件到资源列表
	TArray<USoundCue*> MusicList;
	MusicList.Add(Cast<USoundCue>(MenuStyle->MenuBackgroundMusic.GetResourceObject()));
	TArray<USoundCue*> SoundList;
	SoundList.Add(Cast<USoundCue>(MenuStyle->StartGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->ExitGameSound.GetResourceObject()));
	SoundList.Add(Cast<USoundCue>(MenuStyle->MenuItemChangeSound.GetResourceObject()));

	//添加资源到Map
	MenuAudioResource.Add(FString("Music"),MusicList);
	MenuAudioResource.Add(FString("Sound"),SoundList);

	//重置一下声音
	ResetMenuVolume(MusicVolume,SoundVolume);
}

SlAiDataHandle::SlAiDataHandle()
{
	//SlAiHelper::Debug(FString("initing"));
	InitRecordData();
	InitializedMenuAudio();
}


void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Cultrue)
{
	switch (Cultrue)
	{
		case ECultureTeam::ZH:
			{
				FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
				//UE_LOG(LogTemp,Warning,TEXT("zh"));
				break;
			}
		case ECultureTeam::EN:
			{
				FInternationalization::Get().SetCurrentCulture(TEXT("en"));
				//UE_LOG(LogTemp,Warning,TEXT("en"));
				break;
			}
	}
	CurrentCultrueTeam=Cultrue;
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdataRecordData(
		GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),CurrentCultrueTeam),
		MusicVolume,
		SoundVolume,
		&RecordDataList);
}

void SlAiDataHandle::ResetMenuVolume(float Musicval, float Soundval)
{
	if (Musicval>0)
	{
		MusicVolume=Musicval;
		//循环设置背景音量
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Music"))->CreateIterator());It;++It)
		{
			(*It)->VolumeMultiplier = MusicVolume;
		}
	}
	
	if (Soundval>0)
	{
		SoundVolume=Soundval;
		for (TArray<USoundCue*>::TIterator It(MenuAudioResource.Find(FString("Sound"))->CreateIterator());It;++It)
		{
			(*It)->VolumeMultiplier = SoundVolume;
		}
	}
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdataRecordData(
		GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),CurrentCultrueTeam),
		MusicVolume,
		SoundVolume,
		&RecordDataList);
}

void SlAiDataHandle::InitializeGameData()
{
	//初始化物品属性图
	InitObjectAttr();
	
	InitResourceAttrMap();
}

void SlAiDataHandle::InitObjectAttr()
{
	SlAiSingleton<SlAiJsonHandle>::Get()->ObjectAttrJsonRead(ObjectAttrMap);

	//获取GameStyle
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	//填充笔刷数组
	ObjectBrushList.Add(&GameStyle->EmptyBrush);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_1);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_2);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_3);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_4);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_5);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_6);
	ObjectBrushList.Add(&GameStyle->ObjectBrush_7);
}

void SlAiDataHandle::InitResourceAttrMap()
{
	SlAiSingleton<SlAiJsonHandle>::Get()->ResourceAttrJsonRead(ResourceAttrMap);
	
	/*for (TMap<int, TSharedPtr<ResourceAttribute>>::TIterator It(ResourceAttrMap); It; ++It)
	{
		SlAiHelper::Debug((It->Value)->ToString(), 120.f);
	}*/
}

template <typename TEnum>
FString SlAiDataHandle::GetEnumValueAsString(const FString& Name, TEnum value)
{
	const UEnum* EnumPtr=FindObject<UEnum>(ANY_PACKAGE,*Name,true);
	if (!EnumPtr)
	{
		return FString("InValid");
	}
	return EnumPtr->GetEnumName((int32)value);
}

template <typename TEnum>
TEnum SlAiDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr=FindObject<UEnum>(ANY_PACKAGE,*Name,true);

	if (!EnumPtr)
	{
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}