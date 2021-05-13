// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/JsonHandle.h"

#include "Common/SlAiHelper.h"

JsonHandle::JsonHandle()
{
	RecordDataFileName=FString("RecordData.json");
	RelativePath = FString("Res/ConfigData");
}

bool JsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
{
	if (!FileName.IsEmpty())
	{
		//获取绝对路径
		FString AbsoPath=FPaths::ProjectContentDir()+RelaPath+FileName;
		if (FPaths::FileExists(AbsoPath))
		{
			if (FFileHelper::LoadFileToString(ResultString,*AbsoPath))
			{
				return true;
			}else
			{
				//加载不成功
				SlAiHelper::Debug(AbsoPath+"文件加载错误!");
			}
		}else
		{
			SlAiHelper::Debug(AbsoPath+"文件不存在!");
		}
	}
	return false;
}
