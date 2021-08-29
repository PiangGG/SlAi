// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/SlAiSceneCapture2D.h"

#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"

ASlAiSceneCapture2D::ASlAiSceneCapture2D()
{
	//设置摄像机每帧更新
	GetCaptureComponent2D()->bCaptureEveryFrame=true;

	//设置渲染图片格式
	GetCaptureComponent2D()->CaptureSource = ESceneCaptureSource::SCS_SceneColorSceneDepth;

	//设置视野模式为正交模式
	GetCaptureComponent2D()->ProjectionType = ECameraProjectionMode::Orthographic;
	
	GetCaptureComponent2D()->OrthoWidth = 3000.0f;

	//设置旋转，头朝下
	SetActorRotation(FRotator(-90.0f,0.0f,0.0f));
}

UTextureRenderTarget2D* ASlAiSceneCapture2D::GetMiniMapTex()
{
	//创建渲染贴图
	MiniMapTex=NewObject<UTextureRenderTarget2D>();
	//最好是四的倍数
	MiniMapTex->InitAutoFormat(256,256);
	//绑定渲染到摄相机
	GetCaptureComponent2D()->TextureTarget = MiniMapTex;
	//返回资源
	return MiniMapTex;
}

void ASlAiSceneCapture2D::UpdateTransform(FVector NormLocation, FRotator NormRotator)
{
	//更新位置更新位置为玩家上方的1000
	SetActorLocation(NormLocation+FVector(0.0,0.0,1000.0));
	//更新旋转为玩家的旋转
	SetActorRotation(FRotator(-90.0f,NormRotator.Yaw,NormRotator.Roll));
}

void ASlAiSceneCapture2D::UpdateMiniMapMiniWidth(int Delta)
{
	const float	PreWidth = GetCaptureComponent2D()->OrthoWidth;
	GetCaptureComponent2D()->OrthoWidth = FMath::Clamp<float>(PreWidth+Delta,2000.0f,4000.0f);
}

float ASlAiSceneCapture2D::GetMapSize()
{
	return GetCaptureComponent2D()->OrthoWidth;
}
