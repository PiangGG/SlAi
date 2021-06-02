// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSlAiContainerBaseWidget.h"

/**
 * 
 */
class SLAI_API SSlAiContainerOutputWidget : public SSlAiContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiContainerOutputWidget)
	{}
	SLATE_ATTRIBUTE(int,workIndex)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//重写左键操作
	virtual void LeftOperate(int InputID, int InputNum, int& OutputID, int& OutputNum) override;

	//重写右键操作
	virtual void RightOperate(int InputID, int inputNum, int& OutputID, int& OutputNum) override;
};
