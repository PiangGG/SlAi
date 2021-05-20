// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Data/SlAiTypes.h"
#include "GameFramework/PlayerController.h"
#include "SlAiPlayerController.generated.h"

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
public:
	//获取玩家角色
	class ASlAiPlayerCharacter* SPCharacter;
	class ASlAiPlayerState* SPState;
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
private:
	//左键预动作
	EUpperBody::Type LeftUpperType;
	//右键预动作
	EUpperBody::Type RightUpperType;
	//是否按着鼠标左右键
	bool IsLeftButtonDown;
	bool IsRightButtonDonw;
};
