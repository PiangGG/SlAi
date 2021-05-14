// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiDataHandle.h"

#include "Common/SlAiHelper.h"
#include "Data/SlAiJsonHandle.h"
#include "Data/SlAiSingleton.h"

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

SlAiDataHandle::SlAiDataHandle()
{
	//SlAiHelper::Debug(FString("initing"));
	InitRecordData();
}


void SlAiDataHandle::ChangeLocalizationCulture(ECultureTeam Cultrue)
{
	switch (Cultrue)
	{
		case ECultureTeam::ZH:
			{
				FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
				UE_LOG(LogTemp,Warning,TEXT("zh"));
				break;
			}
		case ECultureTeam::EN:
			{
				FInternationalization::Get().SetCurrentCulture(TEXT("en"));
				UE_LOG(LogTemp,Warning,TEXT("en"));
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
	}
	
	if (Soundval>0)
	{
		SoundVolume=Soundval;
	}
	SlAiSingleton<SlAiJsonHandle>::Get()->UpdataRecordData(
		GetEnumValueAsString<ECultureTeam>(FString("ECultureTeam"),CurrentCultrueTeam),
		MusicVolume,
		SoundVolume,
		&RecordDataList);
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