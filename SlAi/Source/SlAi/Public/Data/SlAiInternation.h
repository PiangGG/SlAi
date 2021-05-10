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
//SlAiInternation::Register(LOCTEXT("SlAiMenu","Menu","Menu"));