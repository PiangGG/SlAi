// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SSlAiContainerBaseWidget.h"

/**
 * 
 */
class SLAI_API SSlAiContainerNormalWidget : public SSlAiContaineBaseWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiContainerNormalWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
