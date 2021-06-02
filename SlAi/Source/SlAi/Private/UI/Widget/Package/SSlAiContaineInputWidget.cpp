// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiContainerInputWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerInputWidget::Construct(const FArguments& InArgs)
{
	SSlAiContainerBaseWidget::Construct(
		SSlAiContainerBaseWidget::FArguments()
		.workIndex(InArgs._workIndex)
	);
}

void SSlAiContainerInputWidget::ResetContainerPara(int ObjectID, int Num)
{
	//定義是否改變
	bool IsChanged = false;
	if (ObjectIndex!=ObjectID||ObjectNum!=Num)IsChanged=true;
	//調用父類事件
	SSlAiContainerBaseWidget::ResetContainerPara(ObjectID,Num);

	//如果有改變，執行合成輸入委托
	if (IsChanged)CompoundInput.ExecuteIfBound();
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
