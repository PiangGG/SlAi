// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "GameFramework/PlayerController.h"
#include "SlAiPlayerController.generated.h"

//修改准心委托
DECLARE_DELEGATE_TwoParams(FUpdatePointer,bool,float)
//显示UI委托
DECLARE_DELEGATE_TwoParams(FShowGameUI,EGameUIType::Type,EGameUIType::Type)
//修改小地图视野范围委托
DECLARE_DELEGATE_OneParam(FUpdateMiniMapWidth,int )
/**
 * 
 */
UCLASS()
class SLAI_API ASlAiPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	ASlAiPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	//对Charactor的手持物品进行更改，这个函数在PlayerState内会调用
	void ChangeHandObject();
public:
	//获取玩家角色
	class ASlAiPlayerCharacter* SPCharacter;
	class ASlAiPlayerState* SPState;

	//实时修改准心的委托,注册的函数是PointerWidget的UpdatePointer
	FUpdatePointer UpdatePointer;

	FShowGameUI ShowGameUI;

	FUpdateMiniMapWidth UpdateMiniMapWidth;
protected:
	virtual  void BeginPlay() override;
private:
	void ChangeView();

	//鼠标按键时间
	void LeftEventStart();
	void LeftEventEnd();

	void RightEventStart();
	void RightEventEnd();
	//滑轮滚动
	void ScrollUpEvent();
	void ScrollDownEvent();
	//修改预动作
	void ChangePreUpperType(EUpperBody::Type RightType);
	//射线检测结果
	FHitResult RayGetHitResult(FVector TraceStart,FVector TraceEnd);
	//绘制射线
	void DrawRayLine(FVector StartPos,FVector EndPos,float Duration);
	//进行射线检测
	void RunRayCast();
	//行为状态机
	void StateMachine();

	//ESC按下事件
	void EscEvent();
	//E键背包
	void PackageEvent();
	//T键聊天室
	void ChatRoomEvent();
	//切换输入模式，true为游戏模式，false 为混合模式
	void SwitchInputMode(bool IsGameOnly);

	//设置锁住输入
	void LockedInput(bool IsLocked);

	//小地图缩放事件
	void AddMapSizeStart();
	void AddMapSizeStop();
	void ReduceMapSizeStart();
	void ReduceMapSizeStop();

	//在Tick函数处理小地图事件
	void TickMiniMap();
private:
	//左键预动作
	EUpperBody::Type LeftUpperType;
	//右键预动作
	EUpperBody::Type RightUpperType;
	//是否按着鼠标左右键
	bool IsLeftButtonDown;
	bool IsRightButtonDonw;

	//检测到的资源
	AActor * RayActor;

	//保存当前UI状态
	EGameUIType::Type CurrentUIType;

	//小地图缩放状态
	EMiniMapSizeMode::Type MiniMapSizeMode;
	
};
