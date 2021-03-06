// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SLAI_API SSlAiMiniMapWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiMiniMapWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//重写绘制函数
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	//委托接受GameMode传递过来的Texture资源
	void RegisterMiniMap(class UTextureRenderTarget2D* MiniMapRender);

	//委托接受GameMode传过来的玩家旋转,绑定委托GameMode的updateMapDirection
	void UpdateMapData(const FRotator PlayerRotator,const float	MiniMapSize,const TArray<FVector2D>* EnemyPosLost,
		const TArray<bool>* EnemyLockList,const TArray<float>* EnemyRotateList);
private:
	//获取GameStyle
	const struct FSlAiGameStyle *GameStyle;

	//显示MiniMap的图片
	TSharedPtr<SImage> MiniMapImage;
	//显示玩家视野图片
	TSharedPtr<SImage> EnemyViewImage;

	//敌人视野材质
	UMaterialInstanceDynamic* EnemyViewMatDynamic;

	struct FSlateBrush* MiniMapBrush;

	//四个方向的渲染位置
	FVector2D NorthLocation;
	FVector2D SouthLocation;
	FVector2D EastLocation;
	FVector2D WestLocation;

	//小地图尺寸
	float MapSize;
	//敌人相对玩家的位置
	TArray<FVector2D> EnemyPos;
	//敌人是否锁定玩家
	TArray<bool> EnemyLock;
};
