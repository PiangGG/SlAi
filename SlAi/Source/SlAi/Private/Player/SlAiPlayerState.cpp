// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerState.h"

ASlAiPlayerState::ASlAiPlayerState()
{
}

void ASlAiPlayerState::RegisterShortcutContainer(TArray<TSharedPtr<ShortcutContainer>>* ContainerList,
                                                 TSharedPtr<STextBlock> ShortcutInfoTextBlock)
{
	for (TArray<TSharedPtr<ShortcutContainer>>::TIterator It(*ContainerList);It;++It)
	{
		ShortcutContainerList.Add(*It);
	}
	ShortcutInfoTextAttr.BindUObject(this,&ASlAiPlayerState::GetShortcutInfoText);
	//绑定快捷栏信息
	ShortcutInfoTextBlock->SetText(ShortcutInfoTextAttr);

	/*
	 * 临时测试代码
	 */
	ShortcutContainerList[1]->SetObject(1)->SetObjectNum(5);
	ShortcutContainerList[2]->SetObject(2)->SetObjectNum(4);
	ShortcutContainerList[3]->SetObject(3)->SetObjectNum(3);
}

FText ASlAiPlayerState::GetShortcutInfoText() const
{
	return FText::FromString("ASlAiPlayerState::GetShortcutInfoText");
}
