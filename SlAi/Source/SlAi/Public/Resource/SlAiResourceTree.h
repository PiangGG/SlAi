// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resource/SlAiResourceObject.h"
#include "SlAiResourceTree.generated.h"

/**
 * 
 */
UCLASS()
class SLAI_API ASlAiResourceTree : public ASlAiResourceObject
{
	GENERATED_BODY()
public:
	ASlAiResourceTree();
	virtual int GetResourceIndex() override;
};
