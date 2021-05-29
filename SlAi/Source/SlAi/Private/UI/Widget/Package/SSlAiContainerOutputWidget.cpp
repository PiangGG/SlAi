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
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
