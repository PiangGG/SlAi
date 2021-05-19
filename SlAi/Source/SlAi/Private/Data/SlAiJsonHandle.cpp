// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiJsonHandle.h"
#include "Common/SlAiHelper.h"

SlAiJsonHandle::SlAiJsonHandle()
{
	RecordDataFileName=FString("RecordData.json");
	ObjectAttrFileName = FString("ObjectAttribute.json");
	RelativePath = FString("Res/ConfigData/");
}

void SlAiJsonHandle::RecordDataJsonRead(FString& Culture, float& MusicVolume, float& SoundVolume,
	TArray<FString>& RecordDataList)
{
	FString JsonValue;
	LoadStringFromFile(RecordDataFileName,RelativePath,JsonValue);
	
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonValue);
	//解析
	if (FJsonSerializer::Deserialize(JsonReader,JsonParsed))
	{
		//获取解析出来的值
		Culture=JsonParsed[0]->AsObject()->GetStringField(FString("Culture"));
		MusicVolume=JsonParsed[1]->AsObject()->GetNumberField(FString("MusicVolume"));
		SoundVolume=JsonParsed[2]->AsObject()->GetNumberField(FString("SoundVolume"));
		//获取存档数据
		TArray<TSharedPtr<FJsonValue>> RecordDataArray = JsonParsed[3]->AsObject()->GetArrayField(FString("RecordData"));

		for (int i=0;i<RecordDataArray.Num();++i)
		{
			FString RecordDataName = RecordDataArray[i]->AsObject()->GetStringField(FString::FromInt(i));
			RecordDataList.Add(RecordDataName);
		}
	}else
	{
		SlAiHelper::Debug(FString("Json解析失败!"));
	}
}

void SlAiJsonHandle::UpdataRecordData(FString Culture, float MusicVolume, float SoundVolume,
	TArray<FString>* RecordDataList)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> BaseDataArray;
	//语言
	TSharedPtr<FJsonObject> CultureObject=MakeShareable(new FJsonObject);
	CultureObject->SetStringField("Culture",Culture);
	TSharedPtr<FJsonValueObject> CultureValue=MakeShareable(new FJsonValueObject(CultureObject));
	//声音
	TSharedPtr<FJsonObject> MusicVolumeObject=MakeShareable(new FJsonObject);
	MusicVolumeObject->SetNumberField("MusicVolume",MusicVolume);
	TSharedPtr<FJsonValueObject> MusicVolumeValue=MakeShareable(new FJsonValueObject(MusicVolumeObject));
	//Sound
	TSharedPtr<FJsonObject> SoundVolumeObject=MakeShareable(new FJsonObject);
	SoundVolumeObject->SetNumberField("SoundVolume",SoundVolume);
	TSharedPtr<FJsonValueObject> SoundVolumeValue=MakeShareable(new FJsonValueObject(SoundVolumeObject));

	TArray<TSharedPtr<FJsonValue>> RecordDataArray;

	for (int i=0;i<RecordDataList->Num();++i)
	{
		TSharedPtr<FJsonObject> RecordItem=MakeShareable(new FJsonObject);
		RecordItem->SetStringField(FString::FromInt(i),(*RecordDataList)[i]);
		TSharedPtr<FJsonValueObject> RecordDataValue=MakeShareable(new FJsonValueObject(RecordItem));
		RecordDataArray.Add(RecordDataValue);
	}

	TSharedPtr<FJsonObject> RecordDataObject = MakeShareable(new FJsonObject);
	RecordDataObject->SetArrayField("RecordData",RecordDataArray);
	TSharedPtr<FJsonValueObject> RecordDataValue =MakeShareable(new FJsonValueObject(RecordDataObject));

	BaseDataArray.Add(CultureValue);
	BaseDataArray.Add(MusicVolumeValue);
	BaseDataArray.Add(SoundVolumeValue);
	BaseDataArray.Add(RecordDataValue);

	JsonObject->SetArrayField("T",BaseDataArray);

	FString JsonStr;
	//字符串写入Json文件
	GetFStringInJsonData(JsonObject,JsonStr);

	//SlAiHelper::Debug("1:"+FString(JsonStr),60.0);

	//去掉多余字符
	JsonStr.RemoveAt(0,8);
	JsonStr.RemoveFromEnd(FString("}"));

	//SlAiHelper::Debug("2:"+FString(JsonStr),60.0);

	//写入文件
	WriteFileWithJsonData(JsonStr,RelativePath,RecordDataFileName);
}

void SlAiJsonHandle::ObjectAttrJsonRead(TMap<int, TSharedPtr<ObjectAttribute>>& ObjectAttrMap)
{
	FString JsonValue;
	LoadStringFromFile(ObjectAttrFileName,RelativePath,JsonValue);
	TArray<TSharedPtr<FJsonValue>> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader=TJsonReaderFactory<TCHAR>::Create(JsonValue);

	if (FJsonSerializer::Deserialize(JsonReader,JsonParsed))
	{
		for (int i= 0;i<JsonParsed.Num();++i)
		{
			TArray<TSharedPtr<FJsonValue>> ObjectAttr=JsonParsed[i]->AsObject()->GetArrayField(FString::FromInt(i));
			FText EN=FText::FromString(ObjectAttr[0]->AsObject()->GetStringField("EN"));
			FText ZH=FText::FromString(ObjectAttr[1]->AsObject()->GetStringField("ZH"));
			FString ObjectTypeStr=ObjectAttr[2]->AsObject()->GetStringField("ObjectType");
			int PlantAttack=ObjectAttr[3]->AsObject()->GetNumberField("PlantAttack");
			int MetalAttack=ObjectAttr[4]->AsObject()->GetNumberField("MetalAttack");
			int AnimalAttack=ObjectAttr[5]->AsObject()->GetNumberField("AnimalAttack");
			int AffectAttack=ObjectAttr[6]->AsObject()->GetNumberField("AffectAttack");
			FString TexPath=ObjectAttr[7]->AsObject()->GetStringField("PlantAttack");
			EObjectType::Type ObjectType=StringToObject(ObjectTypeStr);
			TSharedPtr<ObjectAttribute> ObjectAttrPtr=MakeShareable(new ObjectAttribute(
				EN,ZH,ObjectType,PlantAttack,MetalAttack,AnimalAttack,AffectAttack,TexPath));
			ObjectAttrMap.Add(i,ObjectAttrPtr);
		}	
	}else
	{
		SlAiHelper::Debug(FString("解析失败!"));
	}
}

bool SlAiJsonHandle::LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString)
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
				SlAiHelper::Debug(AbsoPath+FString("文件加载错误!"));
			}
		}else
		{
			SlAiHelper::Debug(AbsoPath+FString("文件不存在!"));
		}
	}
	return false;
}

bool SlAiJsonHandle::GetFStringInJsonData(const TSharedPtr<FJsonObject>& JsonObj, FString& JsonStr)
{
	if (JsonObj.IsValid()&&JsonObj->Values.Num()>0)
	{
		TSharedRef<TJsonWriter<TCHAR>> JsonWriter = TJsonWriterFactory<TCHAR>::Create(&JsonStr);
		//序列化
		FJsonSerializer::Serialize(JsonObj.ToSharedRef(),JsonWriter);
		return true;
	}
	
	return  false;
}

bool SlAiJsonHandle::WriteFileWithJsonData(const FString& JsonStr, const FString& RelaPath, const FString& FileName)
{
	if (!JsonStr.IsEmpty())
	{
		if (!FileName.IsEmpty())
		{
			//获取一下绝对路径
			FString AbsoPath = FPaths::ProjectContentDir()+RelativePath+FileName;
			//保存
			if(FFileHelper::SaveStringToFile(JsonStr,*AbsoPath))
			{
				return true;
			}else
			{
				SlAiHelper::Debug(AbsoPath+FileName+FString("保存失败"));
			}
		}	
	}
	return  false;
}

EObjectType::Type SlAiJsonHandle::StringToObject(const FString ArgStr)
{
	if (ArgStr.Equals(FString("Normal")))return EObjectType::Normal;
	if (ArgStr.Equals(FString("Food")))return EObjectType::Food;
	if (ArgStr.Equals(FString("Tool")))return EObjectType::Tool;
	if (ArgStr.Equals(FString("Weapon")))return EObjectType::Weapon;
	return EObjectType::Normal;
}
