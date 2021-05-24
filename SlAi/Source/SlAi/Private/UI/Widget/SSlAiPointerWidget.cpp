// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiPointerWidget.h"
#include "SlateOptMacros.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SSlAiPointerWidget::Construct(const FArguments& InArgs)
{
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	//初始化大小
	CurrentSize=20.0f;

	IsAimed=false;
	ChildSlot
	[
		// Populate the widget
		SAssignNew(RootBox,SBox)
		.WidthOverride(TAttribute<FOptionalSize>(this,&SSlAiPointerWidget::GetBoxWidget))
		.HeightOverride(TAttribute<FOptionalSize>(this,&SSlAiPointerWidget::GetBoxHeight))
		[
			SNew(SImage)
			.Image(&GameStyle->PointerBursh)
		]
	];
	//加载材质实例
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> StaticPointerMaterialInstance(TEXT("MaterialInstanceConstant'/Game/Material/PointerMatInst.PointerMatInst'"));
	//转化为动态材质实例
	PointerMaterial=(UMaterialInstanceDynamic*)StaticPointerMaterialInstance.Object;
}

void SSlAiPointerWidget::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	//实时修改
	CurrentSize = IsAimed?FMath::FInterpTo(CurrentSize,130.0f,InDeltaTime,10.0f):FMath::FInterpTo(CurrentSize,20.0f,InDeltaTime,10.0f);
}

void SSlAiPointerWidget::UpdatePointer(bool IsAim, float Range)
{
	IsAimed=IsAim;
	PointerMaterial->SetScalarParameterValue(FName("Range"),Range);
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FOptionalSize SSlAiPointerWidget::GetBoxWidget()const
{
	return FOptionalSize(CurrentSize);
}

FOptionalSize SSlAiPointerWidget::GetBoxHeight()const
{
	return FOptionalSize(CurrentSize);
}