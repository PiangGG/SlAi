// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
//语言枚举
UENUM()
enum class ECultureTeam:uint8
{
    EN=0,
	ZH
};

//Menu按钮类型
namespace EMenuItem
{
	enum Type
	{
		None,
		StartGame,
		QuitGame,
		NewGame,
		LoadRecord,
		StartGameGoBack,
		GameOptionGoBack,
		NewGameGoBack,
		ChooseRecordGoBack,
		EnterGame,
		EnterRecord
	};
}