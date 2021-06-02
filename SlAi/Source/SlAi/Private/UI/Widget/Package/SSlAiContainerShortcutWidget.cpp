// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/Package/SSlAiContainerShortcutWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiContainerShortcutWidget::Construct(const FArguments& InArgs)
{
	
	SSlAiContainerBaseWidget::Construct(
		SSlAiContainerBaseWidget::FArguments()
		.workIndex(InArgs._workIndex)
	);
	
}

void SSlAiContainerShortcutWidget::ResetContainerPara(int ObjectID, int Num)
{
	//定義是否改變
	bool IsChanged = false;
	if (ObjectIndex!=ObjectID||ObjectNum!=Num)IsChanged = true;
	//調用父類事件
	SSlAiContainerBaseWidget::ResetContainerPara(ObjectID,Num);

	//如果有改變執行快捷欄更新委托
	if (IsChanged)PackShortChange.ExecuteIfBound(workIndex.Get(),ObjectID,Num);
	{
		
	}
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
