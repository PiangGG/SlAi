// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSlAiContainerBaseWidget.h"


/**
 * 
 */
class SLAI_API SSlAiContainerInputWidget : public SSlAiContainerBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiContainerInputWidget)
	{}
	SLATE_ATTRIBUTE(int,workIndex)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void ResetContainerPara(int ObjectID, int Num) override;
};
