// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Text/SMultiLineEditableText.h"

class SVerticalBox;
struct ChatShowItem;
/**
 * 
 */
class SLAI_API SSlAiChatShowWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SSlAiChatShowWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */

	
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	//添加信息
	void AddMessage(FText NewName,FText NewContent);
private:
	void InitlizeItem();	
private:
	//获取GameStyle
	const struct FSlAiGameStyle* GameStyle;

	TSharedPtr<SVerticalBox> ChatBox;

	//已经激活序列
	TArray<TSharedPtr<ChatShowItem>>ActiveList;
	//未激活序列
	TArray<TSharedPtr<ChatShowItem>> UnActiveList;
};
