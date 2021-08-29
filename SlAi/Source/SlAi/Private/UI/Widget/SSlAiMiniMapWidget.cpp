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
	MiniMapBrush->ImageSize = FVector2D(280.0f,280.0f);
	MiniMapBrush->DrawAs = ESlateBrushDrawType::Image;

	//绑定材质资源文件
	MiniMapBrush->SetResourceObject(MiniMapMatDynamic);
	//将笔刷作为MiniMapImage的笔刷
	MiniMapImage->SetImage(MiniMapBrush);
	
}

void SSlAiMiniMapWidget::UpdateMapData(const FRotator PlayerRotator, const float MiniMapSize,
	const TArray<FVector2D>* EnemyPosLost, const TArray<bool>* EnemyLockList, const TArray<float>* EnemyRotateList)
{
	//获取Yaw，这个Yaw从180到-180，我们把他变成负的，然后通过加角度来计算
	float YawDir = -PlayerRotator.Yaw;

	//使用三角函数来计算
	NorthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir)),FMath::Cos(FMath::DegreesToRadians(YawDir)))*150.f+FVector2D(160.0F,160.0F);
	EastLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir+90.0f)),FMath::Cos(FMath::DegreesToRadians(YawDir+90.0f)))*150.f+FVector2D(160.0F,160.0F);
	SouthLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir+180.0f)),FMath::Cos(FMath::DegreesToRadians(YawDir+180.0f)))*150.f+FVector2D(160.0F,160.0F);
	WestLocation = FVector2D(FMath::Sin(FMath::DegreesToRadians(YawDir+270.0f)),FMath::Cos(FMath::DegreesToRadians(YawDir+270.0f)))*150.f+FVector2D(160.0F,160.0F);
	
}
int32 SSlAiMiniMapWidget::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
	const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
	const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

	//渲染玩家图标
	FSlateDrawElement::MakeBox
	(
		OutDrawElements,
		LayerId+100,
		AllottedGeometry.ToPaintGeometry(FVector2D(155.0F,155.5F),FVector2D(10.0F,10.0F)),
		&GameStyle->PawnPointBrush,
		ESlateDrawEffect::None,
		FLinearColor(1.0f,1.0f,0.0f,1.0f)
	);

	//渲染东西南北
	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId+10,
		AllottedGeometry.ToPaintGeometry(NorthLocation-FVector2D(8.0f,8.0f),FVector2D(16.0F,16.0F)),
		NSLOCTEXT("SlAiGame","N","N"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.0f,1.0f,1.0f,1.0f)
	);

	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId+10,
		AllottedGeometry.ToPaintGeometry(SouthLocation+FVector2D(8.0f,8.0f),FVector2D(16.0F,16.0F)),
		NSLOCTEXT("SlAiGame","S","S"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.0f,1.0f,1.0f,1.0f)
	);

	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId+10,
		AllottedGeometry.ToPaintGeometry(EastLocation+FVector2D(8.0f,8.0f),FVector2D(16.0F,16.0F)),
		NSLOCTEXT("SlAiGame","E","E"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.0f,1.0f,1.0f,1.0f)
	);

	FSlateDrawElement::MakeText
	(
		OutDrawElements,
		LayerId+10,
		AllottedGeometry.ToPaintGeometry(WestLocation+FVector2D(8.0f,8.0f),FVector2D(16.0F,16.0F)),
		NSLOCTEXT("SlAiGame","W","W"),
		GameStyle->Font_16,
		ESlateDrawEffect::None,
		FLinearColor(1.0f,1.0f,1.0f,1.0f)
	);
	return LayerId;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
