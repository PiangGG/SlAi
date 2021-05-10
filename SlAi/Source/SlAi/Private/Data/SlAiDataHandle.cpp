// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiDataHandle.h"

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
SlAiDataHandle::SlAiDataHandle()
{
	//初始化为中文
	CurrentCultrueTeam=ECultureTeam::ZH;
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
}

