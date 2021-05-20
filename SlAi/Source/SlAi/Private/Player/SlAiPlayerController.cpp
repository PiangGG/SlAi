// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerController.h"

#include "Common/SlAiHelper.h"
#include "Player/SlAiPlayerCharacter.h"
#include "Player/SlAiPlayerState.h"

ASlAiPlayerController::ASlAiPlayerController()
{
	//允许每帧允许
	PrimaryActorTick.bCanEverTick=true;
}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASlAiPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//绑定视角切换
	InputComponent->BindAction("ChangeView",IE_Pressed,this,&ASlAiPlayerController::ChangeView);
	//绑定鼠标按下事件
	InputComponent->BindAction("LeftEvent",IE_Pressed,this,&ASlAiPlayerController::LeftEventStart);
	InputComponent->BindAction("LeftEvent",IE_Released,this,&ASlAiPlayerController::LeftEventEnd);
	InputComponent->BindAction("RightEvent",IE_Pressed,this,&ASlAiPlayerController::RightEventStart);
	InputComponent->BindAction("RightEvent",IE_Released,this,&ASlAiPlayerController::RightEventEnd);

	InputComponent->BindAction("ScrollUp",IE_Pressed,this,&ASlAiPlayerController::ScrollUpEvent);
	InputComponent->BindAction("ScrollDown",IE_Pressed,this,&ASlAiPlayerController::ScrollDownEvent);
}

void ASlAiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//获取角色状态
	if (!SPCharacter)SPCharacter = Cast<ASlAiPlayerCharacter>(GetCharacter());
	if(!SPState)SPState=Cast<ASlAiPlayerState>(PlayerState);
	//设置鼠标不显示
	bShowMouseCursor=false;
	//设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);

	//设置预动作
	LeftUpperType = EUpperBody::Punch;
	RightUpperType = EUpperBody::PickUp;

	IsRightButtonDonw = false;
	IsLeftButtonDown = false;
}

void ASlAiPlayerController::ChangeView()
{
	//如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch)return;
	switch (SPCharacter->GameView)
	{
	case EGameViewMode::First:
		SPCharacter->ChangeView(EGameViewMode::Third);
		break;
	case EGameViewMode::Third:
		SPCharacter->ChangeView(EGameViewMode::First);
		break;
	}
}

void ASlAiPlayerController::LeftEventEnd()
{
	SPCharacter->upperType=EUpperBody::None;
	IsLeftButtonDown = false;
}

void ASlAiPlayerController::RightEventStart()
{
	SPCharacter->upperType=RightUpperType;
	IsRightButtonDonw= true;
}

void ASlAiPlayerController::RightEventEnd()
{
	SPCharacter->upperType=EUpperBody::None;
	IsRightButtonDonw = false;
}

void ASlAiPlayerController::ScrollUpEvent()
{
	SlAiHelper::Debug(FString("ScrollUpEvent"));
	//如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch)return;
	//如果左右键按下就不准跳转
	if(IsLeftButtonDown||IsRightButtonDonw)return;
	//告诉状态类切换
	SPState->ChoosedShortcut(true);
}

void ASlAiPlayerController::ScrollDownEvent()
{
	SlAiHelper::Debug(FString("ScrollDownEvent"));
	//如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch)return;
	//如果左右键按下就不准跳转
	if(IsLeftButtonDown||IsRightButtonDonw)return;
	//告诉状态类切换
	SPState->ChoosedShortcut(false);
}

void ASlAiPlayerController::LeftEventStart()
{
	SPCharacter->upperType=LeftUpperType;
	IsLeftButtonDown = true;
}
