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
}
SlAiDataHandle::SlAiDataHandle()
{
}


void SlAiDataHandle::ChangeLocalizationCultrue(ECultrueTeam Cultrue)
{
	switch (Cultrue)
	{
		case ECultrueTeam::CH:
			{
				FInternationalization::Get().SetCurrentCulture(TEXT("CH"));
				break;
			}
		case ECultrueTeam::EN:
			{
				FInternationalization::Get().SetCurrentCulture(TEXT("EN"));
				break;
			}
	}
	CurrentCultrueTeam=Cultrue;
}
