// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
namespace  SlAiHelper
{
	FORCEINLINE void Debug(FString Message,float Duration = 3.0f)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,Duration,FColor::Yellow,Message);
		}
	}

	template<class UserClass>
	FORCEINLINE FTimerHandle PlayerSoundAndCall(UWorld* World,const FSlateSound Sound,
		UserClass*InUserObject,typename FTimerDelegate::TRawMethodDelegate<UserClass>::FMethodPtr InMethod)
	{
		FSlateApplication::Get().PlaySound(Sound);
		FTimerHandle Result;
		const float SoundDuration = FMath::Max(FSlateApplication::Get().GetSoundDuration(Sound),0.1f);
		FTimerDelegate Callback;
		Callback.BindRaw(InUserObject,InMethod);
		World->GetTimerManager().SetTimer(Result,Callback,SoundDuration,false);
		return  Result;
	}
}
