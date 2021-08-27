// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/SSlAiMiniMapWidget.h"
#include "SlateOptMacros.h"
#include "Engine/TextureRenderTarget2D.h"
#include "UI/Style/SlAiGameWidgetStyle.h"
#include "UI/Style/SlAIStyle.h"
#include "Widgets/Images/SImage.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SSlAiMiniMapWidget::Construct(const FArguments& InArgs)
{
	//获取GameStyle
	GameStyle=&SlAiStyle::Get().GetWidgetStyle<FSlAiGameStyle>("BPSlAiGameStyle");
	ChildSlot
	[
		// Populate the widget
		SNew(SBox)
		.WidthOverride(320.0F)
		.HeightOverride(320.0F)
		[
			SNew(SOverlay)
			+SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.Image(&GameStyle->MiniMapBursh)
			]
			//渲染MiniMap图片
			+SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SAssignNew(MiniMapImage,SImage)
			]
		]
	];
	
}

void SSlAiMiniMapWidget::RegisterMiniMap(UTextureRenderTarget2D* MiniMapRender)
{
	//获取材质，这个材质是遮罩
	UMaterialInterface* MiniMapInst = LoadObject<UMaterialInterface>(NULL,TEXT("MaterialInstanceConstant'/Game/Material/MinniMapMatInst.MinniMapMatInst'"));
	//创建动态材质
	UMaterialInstanceDynamic * MiniMapMatDynamic = UMaterialInstanceDynamic::Create(MiniMapInst,nullptr);
	//绑定材质属性
	MiniMapMatDynamic->SetTextureParameterValue(FName("MiniMapTex"),MiniMapRender);

	//创建MiniMap笔刷
	MiniMapBrush = new FSlateBrush();
	MiniMapBrush->ImageSize = FVector2D(300.0f,300.0f);
	MiniMapBrush->DrawAs = ESlateBrushDrawType::Image;

	//绑定材质资源文件
	MiniMapBrush->SetResourceObject(MiniMapMatDynamic);
	//将笔刷作为MiniMapImage的笔刷
	MiniMapImage->SetImage(MiniMapBrush);
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
