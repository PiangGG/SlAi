// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiContainerOutputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerOutputWidget::Construct(const FArguments& InArgs)
{
	SSlAiContainerBaseWidget::Construct(
		SSlAiContainerBaseWidget::FArguments()
		.workIndex(InArgs._workIndex)
	);
}

void SSlAiContainerOutputWidget::LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum)
{
	//如果本地物体为空
	if (ObjectIndex ==0)
	{
		OutputID = InputID;
		OutputNum = InputNum;
		return;
	}

	//一下都是输入物体不为空的状态
	//如果输入的物体与本地物品相同并且可以叠加
	if (InputID==ObjectIndex&&MultiplyAble(InputID))
	{
		OutputID = ObjectIndex;
		OutputNum = (InputNum+ObjectNum<=64)?(InputNum+ObjectNum):64;
		ObjectNum = (InputNum+ObjectNum<=64)?0:(InputNum+ObjectNum-64);
		//执行合成输出委托
		CompoundOutput.ExecuteIfBound(ObjectIndex,OutputNum-InputNum);
		return;
	}
	//如果物品不相同或者物品相同但是不能叠加,输出物品，丢弃物品
	OutputID = ObjectIndex;
	OutputNum = ObjectNum;
	//执行合成输出委托
	CompoundOutput.ExecuteIfBound(ObjectIndex,ObjectNum);
	//执行丢弃物品委托
	ThrowObject.ExecuteIfBound(InputID,InputNum);
}

void SSlAiContainerOutputWidget::RightOperate(int InputID, int inputNum, int& OutputID, int& OutputNum)
{
	//如果本地物品为空
	if (ObjectIndex==0)
	{
		OutputID = InputID;
		OutputNum = inputNum;
		return;
	}
	//以下是本地物体不为空的情况

	//如果输入为空,直接给出本地的一半
	if (InputID==0)
	{
		OutputID=ObjectIndex;
		//区别单数双数
		OutputNum = (ObjectNum%2 ==1)?(ObjectNum/2+1):(ObjectNum/2);
		//执行合成输出委托
		CompoundOutput.ExecuteIfBound(ObjectIndex,OutputNum);
		//更新属性
		ResetContainerPara(ObjectNum-OutputNum==0?0:ObjectIndex,ObjectNum-OutputNum);
		//直接返回
		return;
	}
	//如果物品相同并且可以合并
	if (InputID==ObjectIndex&&MultiplyAble(InputID))
	{
		OutputID = ObjectIndex;
		//预备输出的数量
		int PreOutputNum = (ObjectNum%2==1)?(ObjectNum/2+1):(ObjectNum/2);
		//实际输出的数量
		OutputNum = (PreOutputNum+inputNum<=64)?(PreOutputNum+inputNum):64;
		ObjectNum = ObjectNum-(OutputNum-InputID);
		//执行合成输出委托
		CompoundOutput.ExecuteIfBound(ObjectIndex,OutputNum-inputNum);
		//更新属性
		//ResetContainerPara(ObjectNum==0,OutputNum-inputNum);
		//直接返回
		return;;
	}

	//如果物品不相同或者相同但是不能合并，把输入物品丢弃，输出本地物品的一半
	OutputID = ObjectIndex;
	//区别单双数
	OutputNum = (ObjectNum%2==1)?(ObjectNum/2+1):(ObjectNum/2);
	//执行合成委托
	CompoundOutput.ExecuteIfBound(ObjectIndex,OutputNum);
	//执行丢弃物品委托
	ThrowObject.ExecuteIfBound(InputID,inputNum);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
