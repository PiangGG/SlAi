// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiContainerBaseWidget.h"
#include "SlateOptMacros.h"
#include "Data/SlAiDataHandle.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "UI/Widget/Package/SSlAiContainerInputWidget.h"
#include "UI/Widget/Package/SSlAiContainerNormalWidget.h"
#include "UI/Widget/Package/SSlAiContainerOutputWidget.h"
#include "UI/Widget/Package/SSlAiContainerShortcutWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerBaseWidget::Construct(const FArguments& InArgs)
{
	//获取style
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	//获取工作号
	workIndex = InArgs._workIndex;

	IsHover =false;
	ChildSlot
	[
		// Populate the widget
		SAssignNew(ContainerBorder,SBorder)
		.BorderImage(&GameStyle->NormalContainerBrush)
		.Padding(FMargin(8.0f))
		[
			SAssignNew(ObjectImage,SBorder)
			.BorderImage(&GameStyle->EmptyBrush)
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.Padding(FMargin(0.f,0.f,4.f,0.f))
			[
				SAssignNew(ObjectNumText,STextBlock)
				.Font(GameStyle->Font_16)
				.ColorAndOpacity(GameStyle->FontColor_Black)
			]
		]
	];
	IsHover = false;

	//初始化序号都为0
	ObjectIndex= ObjectNum=0;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
TSharedPtr<SSlAiContainerBaseWidget> SSlAiContainerBaseWidget::CreateContainer(EContainerType::Type NeedType, int workId)
{
	TSharedPtr<SSlAiContainerBaseWidget> ResultContainer;
	switch (NeedType)
	{
	case EContainerType::Output:
		SAssignNew(ResultContainer,SSlAiContainerOutputWidget).workIndex(workId);
		break;
	case EContainerType::Input:
		SAssignNew(ResultContainer,SSlAiContainerInputWidget).workIndex(workId);
		break;
	case EContainerType::Normal:
		SAssignNew(ResultContainer,SSlAiContainerNormalWidget).workIndex(workId);
		break;
	case EContainerType::Shortcut:
		SAssignNew(ResultContainer,SSlAiContainerShortcutWidget).workIndex(workId);
		break;
	}
	return ResultContainer;
}

void SSlAiContainerBaseWidget::UpdateHovered(bool IsHovered)
{
	//如果鼠标移动到上边
	if (IsHovered)
	{
		if(!IsHover)ContainerBorder->SetBorderImage(&GameStyle->ChoosedContainerBrush);
	}else
	{
		if(IsHover)ContainerBorder->SetBorderImage(&GameStyle->NormalContainerBrush);
	}
	IsHover = IsHovered;
		
}

void SSlAiContainerBaseWidget::ResetContainerPara(int ObjectID, int Num)
{
	//如果输入ID不相同,更新贴图
	if (ObjectIndex!=ObjectID)ObjectImage->SetBorderImage(SlAiDataHandle::Get()->ObjectBrushList[ObjectID]);

	ObjectIndex = ObjectID;
	ObjectNum=Num;
	//如果物品ID为0
	if (ObjectIndex == 0)
	{
		ObjectNumText->SetText(FText::FromString(""));
	}else
	{
		//判断是否可以叠加
		if (MultiplyAble(ObjectIndex))
		{
			ObjectNumText->SetText(FText::FromString(FString::FromInt(ObjectNum)));
		}else
		{
			ObjectNumText->SetText(FText::FromString(""));
		}
	}
}

int SSlAiContainerBaseWidget::GetIndex() const
{
	return ObjectIndex;
}

int SSlAiContainerBaseWidget::GetNum() const
{
	return ObjectNum;
}

void SSlAiContainerBaseWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//如果输入物品与本地物品相同，并且可以叠加
	if (InputID==ObjectIndex&&MultiplyAble(ObjectIndex))
	{
		//根据数量判断返回的ID
		OutputID = (ObjectNum+InputNum<=64)?0:InputID;
		//如果小于64,返回0，大于则返回差值
		OutputNum = (ObjectNum+InputNum<=64)?0:(ObjectNum+InputNum-64);
		//设置本地数量,上限为64
		ObjectNum = (ObjectNum+InputNum<=64)?(ObjectNum+InputNum):64;
		//更新属性
		ResetContainerPara(ObjectIndex,ObjectNum);
		//直接返回
		return;;
	}
	//直接更换数据
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	//更新属性
	ResetContainerPara(InputID,InputNum);
}

void SSlAiContainerBaseWidget::RightOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//如果输入为空,直接把本地一半给出去,使用进去
	if (InputID==0)
	{
		OutputID=ObjectIndex;
		//区分单双数
		OutputNum = (ObjectNum%2==1)?(ObjectNum/2+1):(ObjectNum/2);
		//更新属性
		ResetContainerPara(ObjectNum-OutputNum==0?0:ObjectIndex, ObjectNum-OutputNum);
		return;
	}
	//如果物品相同并且物品可以合并 或者本地物品为空，添加一个到本地
	if (ObjectIndex==0||(InputID==ObjectIndex&&MultiplyAble(InputID)))
	{
		//根据本地数量是否超出范围绑定输出数量
		OutputNum = (ObjectNum+1<=64)?(InputNum-1):InputNum;
		OutputID = (OutputNum==0)?0:InputID;
		//更新属性
		ResetContainerPara(InputID,(ObjectNum+1<=64)?(ObjectNum+1):ObjectNum);
		return;
	}

	//如果物品不相同或者相同但是不能合并，直接交换
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	ResetContainerPara(InputID,InputNum);
}

bool SSlAiContainerBaseWidget::MultiplyAble(int ObjectID)
{
	//获取物品属性
	TSharedPtr<ObjectAttribute> ObjectAttr = *SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectID);
	//返回是否是武器或者工具
	return  (ObjectAttr->ObjectType!=EObjectType::Tool&&ObjectAttr->ObjectType!=EObjectType::Weapon);
}
