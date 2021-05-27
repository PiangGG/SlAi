// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/SlAiGameHUD.h"

#include <ThirdParty/CryptoPP/5.6.5/include/misc.h>

#include "GamePlay/SlAiGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SlAiPlayerController.h"
#include "Player/SlAiPlayerState.h"
#include "UI/Widget/SSlAiGameHUDWidget.h"
#include "UI/Widget/SSlAiPlayerStateWidget.h"
#include "UI/Widget/SSlAiPointerWidget.h"
#include "UI/Widget/SSlAiRayInfoWidget.h"
#include "UI/Widget/SSlAiShortcutWidget.h"
#include "Widgets/SWeakWidget.h"

ASlAiGameHUD::ASlAiGameHUD()
{
	if (GEngine&&GEngine->GameViewport)
	{
		SAssignNew(GameHUDWidget,SSlAiGameHUDWidget);
		GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(GameHUDWidget.ToSharedRef()));
	}
}

void ASlAiGameHUD::BeginPlay()
{
	Super::BeginPlay();
	GM=Cast<ASlAiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	//确保
	if (!GM)return;
	//确保要调用的组件都已经实现
	GM->InitGamePlayModule();

	GameHUDWidget->ShortcutWidget->RegisterShortCutContainer.
	BindUObject(GM->SPState,&ASlAiPlayerState::RegisterShortcutContainer);
	
	//绑定注册信息绑定文本事件
	GameHUDWidget->RayInfoWidget->RegisterRayInfoEvent.BindUObject(GM->SPState,&ASlAiPlayerState::RegisterRayInfoEvent);

	//绑定修改准心委托
	GM->SPController->UpdatePointer.BindRaw(GameHUDWidget->PointerWidget.Get(),&SSlAiPointerWidget::UpdatePointer);
	//绑定更新玩家状态委托
	GM->SPState->UpdateStateWidget.BindRaw(GameHUDWidget->PlayerStateWidget.Get(),&SSlAiPlayerStateWidget::UpdateStateWidget);
}
