// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Style/SlAIStyle.h"

#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"

//单例模式,不能写在构造函数中，否则会报为空
TSharedPtr<FSlateStyleSet> SlAiStyle::SlAiStyleInstance = NULL;
//初始化,类似单例
void SlAiStyle::Initialze()
{
	//如果不存在就创建，并注册这个单例
	if (!SlAiStyleInstance.IsValid())
	{
		SlAiStyleInstance=Create();
		//注册
		FSlateStyleRegistry::RegisterSlateStyle(*SlAiStyleInstance);
	}
}
//得到类型名字
FName SlAiStyle::GetStyleSetName()
{
	//FName:系统需要定的名字
	//FString：最耗资源的,对字符串编辑
	//FText:本地化,如果需要本地化需要使用这个
	static FName StyleSetName(TEXT("SlAiStyle"));
	return StyleSetName;
}
//关闭:取消注册这个单例，确保是唯一的，将单例释放
void SlAiStyle::ShutDown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*SlAiStyleInstance);
	ensure(SlAiStyleInstance.IsUnique());
	SlAiStyleInstance.Reset();
}
//找到这个注册单例
const ISlateStyle& SlAiStyle::Get()
{
	return *SlAiStyleInstance;
}

//作者修改为了TSharedRef：进行查找，在指定的路径下面查找TSharedRef<FSlatStyleSet>
TSharedRef<class FSlateStyleSet> SlAiStyle::Create()
{
	TSharedRef<class FSlateStyleSet> StyleRef=FSlateGameResources::New(SlAiStyle::GetStyleSetName(),
		"/Game/UI/Style",
		"/Game/UI/Style");
	return StyleRef;
}
