// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "GameFramework/PlayerController.h"
#include "SlAiPlayerController.generated.h"

//修改准心委托
DECLARE_DELEGATE_TwoParams(FUpdatePointer,bool,float)
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
	
private:
	//左键预动作
	EUpperBody::Type LeftUpperType;
	//右键预动作
	EUpperBody::Type RightUpperType;
	//是否按着鼠标左右键
	bool IsLeftButtonDown;
	bool IsRightButtonDonw;
};
