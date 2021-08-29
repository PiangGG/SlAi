// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SLAI_API SlAiInternation
{
public:
	static void Register(FText value)
	{
		return;
	}
};
#define LOCTEXT_NAMESPACE "SlAiMenu"
SlAiInternation::Register(LOCTEXT("Menu","Menu"));
SlAiInternation::Register(LOCTEXT("StartGame","StartGame"));
SlAiInternation::Register(LOCTEXT("GameOption","GameOption"));
SlAiInternation::Register(LOCTEXT("QuitGame","QuitGame"));

SlAiInternation::Register(LOCTEXT("NewGame","NewGame"));
SlAiInternation::Register(LOCTEXT("LoadRecord","LoadRecord"));
SlAiInternation::Register(LOCTEXT("ChooseRecord","ChooseRecord"));

SlAiInternation::Register(LOCTEXT("RecordName","RecordName"));
SlAiInternation::Register(LOCTEXT("EnterGame","EnterGame"));
SlAiInternation::Register(LOCTEXT("EnterRecord","EnterRecord"));

SlAiInternation::Register(LOCTEXT("RepeatedNameHint","Input Record Name!"));
SlAiInternation::Register(LOCTEXT("NameRepeatedHint","Record Name Repeated!"));

SlAiInternation::Register(LOCTEXT("Chinese","Chinese");
SlAiInternation::Register(LOCTEXT("English","English");
SlAiInternation::Register(LOCTEXT("Music","Music");
SlAiInternation::Register(LOCTEXT("Sound","Sound");
SlAiInternation::Register(LOCTEXT("GoBack","GoBack");
	

#undef LOCTEXT_NAMESPACE
//在一个域名空间内的本地化，同上define
//SlAiInternation::Register(NSLOCTEXT("SlAiMenu", "Menu", "Menu"));

#define LOCTEXT_NAMESPACE "SlAiGame"


SlAiInternation::Register(LOCTEXT("E", "E"));//东
SlAiInternation::Register(LOCTEXT("S", "S"));//南
SlAiInternation::Register(LOCTEXT("W", "W"));//西
SlAiInternation::Register(LOCTEXT("N", "N"));//北

SlAiInternation::Register(LOCTEXT("Player", "Player"));//玩家
SlAiInternation::Register(LOCTEXT("Enemy", "Enemy"));//敌人

SlAiInternation::Register(LOCTEXT("EnemyDialogue", ": Fight with me !"));//敌人的对话
SlAiInternation::Register(LOCTEXT("Send", "Send"));//发送

SlAiInternation::Register(LOCTEXT("GameOption", "GameOption"));//游戏设置
SlAiInternation::Register(LOCTEXT("SaveGame", "SaveGame"));//保存游戏
SlAiInternation::Register(LOCTEXT("SaveCompleted", "SaveCompleted"));//保存完毕
SlAiInternation::Register(LOCTEXT("QuitGame", "QuitGame"));//退出游戏
SlAiInternation::Register(LOCTEXT("GoBack", "GoBack"));//返回


#undef LOCTEXT_NAMESPACE