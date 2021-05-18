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
		GameOption,
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
/*
 * Menu界面類型
 */
namespace EMenuType
{
	enum Type
	{
		None,
		MainMenu,
		StartGame,
		GameOption,
		NewGame,
		ChooseRecord
	};
}

namespace EMenuAnim
{
	enum Type
	{
		Stop,
		Close,
		Open
	};
}
//视角模式
namespace EGameViewMode
{
	enum Type
	{
		First,
		Third
	};
	
}

namespace EUpperBody
{
	enum Type
	{
		None,
		Punch,
		Hit,
		Fight,
		PickUp,
		Eat
	};
}