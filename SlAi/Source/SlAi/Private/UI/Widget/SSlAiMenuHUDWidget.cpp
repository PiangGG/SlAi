// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMenuHUDWidget.h"
#include "SlateOptMacros.h"
//#include "SButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiMenuHUDWidget::Construct(const FArguments& InArgs)
{
	
	ChildSlot
		[
			// Populate the widget
			SNew(SButton)
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
