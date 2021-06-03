// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerController.h"

#include "Camera/CameraComponent.h"
#include "Common/SlAiHelper.h"
#include "Components/LineBatchComponent.h"
#include "Data/SlAiDataHandle.h"
#include "Hand/SlAiHandObject.h"
#include "PickUp/SlAiPickUpObject.h"
#include "Player/SlAiPlayerCharacter.h"
#include "Player/SlAiPlayerState.h"
#include "Resource/SlAiResourceObject.h"

ASlAiPlayerController::ASlAiPlayerController()
{
	//允许每帧允许
	PrimaryActorTick.bCanEverTick=true;
}

void ASlAiPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	RunRayCast();
	//处理动作状态
	StateMachine();
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

	InputComponent->BindAction("EscEvent",IE_Pressed,this,&ASlAiPlayerController::EscEvent).bExecuteWhenPaused = true;
	InputComponent->BindAction("PackageEvent",IE_Pressed,this,&ASlAiPlayerController::PackageEvent);
	InputComponent->BindAction("ChatRoomEvent",IE_Pressed,this,&ASlAiPlayerController::ChatRoomEvent);
}

void ASlAiPlayerController::ChangeHandObject()
{
	//生成手持物品
	SPCharacter->ChangeHandObject(ASlAiHandObject::SpawnHandObject(SPState->GetCurrentHandObjectIndex()));
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

	CurrentUIType = EGameUIType::Game;
}

void ASlAiPlayerController::ChangeView()
{
	if (SPCharacter->IsInputLocaked)return;
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
	if (SPCharacter->IsInputLocaked)return;
	SPCharacter->upperType=EUpperBody::None;
	IsLeftButtonDown = false;
}

void ASlAiPlayerController::RightEventStart()
{
	if (SPCharacter->IsInputLocaked)return;
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
	if (SPCharacter->IsInputLocaked)return;
	//SlAiHelper::Debug(FString("ScrollUpEvent"));
	//如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch)return;
	//如果左右键按下就不准跳转
	if(IsLeftButtonDown||IsRightButtonDonw)return;
	//告诉状态类切换
	SPState->ChoosedShortcut(true);
	
	ChangeHandObject();
}

void ASlAiPlayerController::ScrollDownEvent()
{
	if (SPCharacter->IsInputLocaked)return;
	//SlAiHelper::Debug(FString("ScrollDownEvent"));
	//如果不允许切换直接返回
	if (!SPCharacter->IsAllowSwitch)return;
	//如果左右键按下就不准跳转
	if(IsLeftButtonDown||IsRightButtonDonw)return;
	//告诉状态类切换
	SPState->ChoosedShortcut(false);
	
	ChangeHandObject();
}

void ASlAiPlayerController::ChangePreUpperType(EUpperBody::Type RightType = EUpperBody::None)
{
	//根据当前手持物品修改预动作
	switch (SPState->GetCurrentObjectType())
	{
		case EObjectType::Normal:
			LeftUpperType = EUpperBody::Punch;
			RightUpperType = RightType;
			break;
		case EObjectType::Food:
			LeftUpperType = EUpperBody::Punch;
			RightUpperType = RightType==EUpperBody::None?EUpperBody::Eat:RightType;
			break;
		case EObjectType::Tool:
			LeftUpperType = EUpperBody::Hit;
			RightUpperType = RightType;
			break;
		case EObjectType::Weapon:
			LeftUpperType = EUpperBody::Fight;
			RightUpperType = RightType;
			break;
	}
}

FHitResult ASlAiPlayerController::RayGetHitResult(FVector TraceStart, FVector TraceEnd)
{
	FCollisionQueryParams TraceParams(true);
	TraceParams.AddIgnoredActor(SPCharacter);
	//TraceParams.bTraceAsyncScene=true;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = true;
	FHitResult Hit(ForceInit);
	if (GetWorld()->LineTraceSingleByChannel(Hit,TraceStart,TraceEnd,ECC_GameTraceChannel1,TraceParams))
	{
		DrawRayLine(TraceStart,TraceEnd,5.0f);		
	}
	return Hit;
}

void ASlAiPlayerController::DrawRayLine(FVector StartPos, FVector EndPos, float Duration)
{
	ULineBatchComponent* const LineBatcher=GetWorld()->PersistentLineBatcher;
	if (LineBatcher!=nullptr)
	{
		float LineDuration = (Duration>0.0f)?Duration:LineBatcher->DefaultLifeTime;
		//LineBatcher->DrawLine(StartPos,EndPos,FLinearColor::Red,10.0f,LineDuration);
	}
}

void ASlAiPlayerController::RunRayCast()
{
	FVector StartPos(0.0f);
	FVector EndPos(0.0f);
	switch (SPCharacter->GameView)
	{
		case EGameViewMode::First:
			StartPos=SPCharacter->FirstCamera->GetComponentLocation();
			//StartPos=SPCharacter->FirstCamera->K2_GetComponentLocation();
			EndPos=StartPos+SPCharacter->FirstCamera->GetForwardVector()*2000.f;
			break;
		case EGameViewMode::Third:
			StartPos=SPCharacter->ThirdCamera->GetComponentLocation();
			StartPos=StartPos+SPCharacter->ThirdCamera->GetForwardVector()*300.f;
			EndPos=StartPos+SPCharacter->ThirdCamera->GetForwardVector()*2000.f;
			break;
	}
	//是否检测到物品
	bool IsDetected = false;
	FHitResult Hit = RayGetHitResult(StartPos,EndPos);

	RayActor = Hit.GetActor();
	
	if (Cast<ASlAiPickUpObject>(RayActor))
	{
		IsDetected=true;
		SPState->RayInfoText = Cast<ASlAiPickUpObject>(RayActor)->GetInfoText();
	}
	if (Cast<ASlAiResourceObject>(RayActor))
	{
		IsDetected=true;
		SPState->RayInfoText = Cast<ASlAiResourceObject>(RayActor)->GetInfoText();
	}
	if (!IsDetected)
	{
		SPState->RayInfoText = FText();
	}
}

void ASlAiPlayerController::StateMachine()
{
	//临时
	ChangePreUpperType(EUpperBody::None);
	
	if (!Cast<ASlAiResourceObject>(RayActor)&&!Cast<ASlAiPickUpObject>(RayActor))
	{
		//准心显示白色未锁定
		UpdatePointer.ExecuteIfBound(false,1.0f);
	}
	//如果检测到资源
	if (Cast<ASlAiResourceObject>(RayActor))
	{
		//SlAiHelper::Debug(FString(RayActor->GetName()));
		if (!IsLeftButtonDown)
		{
			//准心显示白色锁定
			UpdatePointer.ExecuteIfBound(false,0.0f);
		}
		if (IsLeftButtonDown&&FVector::Distance(RayActor->GetActorLocation(),SPCharacter->GetActorLocation())<SPState->GetAffectRange())
		{
			//获取实际伤害
			int Damage= SPState->GetDamageValue(Cast<ASlAiResourceObject>(RayActor)->GetResourceType());
			//让资源受伤并获取剩余血量百分比
			float Range =Cast<ASlAiResourceObject>(RayActor)->TakeObjectDamage(Damage)->GetHPRange();
			//更新准心
			UpdatePointer.ExecuteIfBound(true,Range);
		}
	}
	//如果检测到可拾取物品，并且两者的距离小于300
	if (Cast<ASlAiPickUpObject>(RayActor)&&FVector::Distance(RayActor->GetActorLocation(),SPCharacter->GetActorLocation())<300.0f)
	{
		//SlAiHelper::Debug(FString("123"));
		//改变右手预状态为拾取
		ChangePreUpperType(EUpperBody::PickUp);
		//修改准心锁定模式
		UpdatePointer.ExecuteIfBound(false,0);
		//如果右键按下
		if (IsRightButtonDonw&&SPCharacter->IsPackageFree(Cast<ASlAiPickUpObject>(RayActor)->ObjectIndex))
		{
			//吧物品捡起来
			SPCharacter->AddPackageObject(Cast<ASlAiPickUpObject>(RayActor)->TakePickUp());
		}
	}
}

void ASlAiPlayerController::EscEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		//设置游戏暂停
		SetPause(true);
		//设置输入模式为GameAndUI
		SwitchInputMode(false);
		//更新界面
		ShowGameUI.ExecuteIfBound(CurrentUIType,EGameUIType::Pause);
		//更新当前UI
		CurrentUIType=EGameUIType::Pause;
		LockedInput(true);
		break;
	case EGameUIType::Pause: ;
	case EGameUIType::Package: ;
	case EGameUIType::ChatRoom:
		SetPause(false);
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType,EGameUIType::Game);
		CurrentUIType=EGameUIType::Game;
		LockedInput(false);
		break;
	}
}

void ASlAiPlayerController::PackageEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType,EGameUIType::Package);
		CurrentUIType=EGameUIType::Package;
		LockedInput(true);
		break;
	case EGameUIType::Package:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType,EGameUIType::Game);
		CurrentUIType=EGameUIType::Game;
		LockedInput(false);
		break;

	}
}

void ASlAiPlayerController::ChatRoomEvent()
{
	switch (CurrentUIType)
	{
	case EGameUIType::Game:
		SwitchInputMode(false);
		ShowGameUI.ExecuteIfBound(CurrentUIType,EGameUIType::ChatRoom);
		CurrentUIType=EGameUIType::ChatRoom;
		LockedInput(true);
		break;
	case EGameUIType::ChatRoom:
		SwitchInputMode(true);
		ShowGameUI.ExecuteIfBound(CurrentUIType,EGameUIType::Game);
		CurrentUIType=EGameUIType::Game;
		LockedInput(false);
		break;
	default: ;
	}
}

void ASlAiPlayerController::SwitchInputMode(bool IsGameOnly)
{
	if (IsGameOnly)
	{
		bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(true);
		SetInputMode(InputMode);
	}else
	{
		bShowMouseCursor = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
	}
}

void ASlAiPlayerController::LockedInput(bool IsLocked)
{
	SPCharacter->IsInputLocaked = IsLocked;
}

void ASlAiPlayerController::LeftEventStart()
{
	if (SPCharacter->IsInputLocaked)return;
	
	SPCharacter->upperType=LeftUpperType;
	IsLeftButtonDown = true;
}
