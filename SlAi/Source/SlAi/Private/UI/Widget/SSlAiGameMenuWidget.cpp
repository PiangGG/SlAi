// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiGameMenuWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiGameMenuWidget::Construct(const FArguments& InArgs)
{

	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(400.0f)
		.HeightOverride(400.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("GameMenu"))
		]
	];
	
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
