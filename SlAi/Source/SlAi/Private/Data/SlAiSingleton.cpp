// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/SlAiSingleton.h"

template <class T>
TSharedPtr<T> SlAiSingleton<T>::TInstance=NULL;
template <class T>
TSharedPtr<T> SlAiSingleton<T>::Get()
{
	Initialize();
	return TInstance;
}

template <class T>
void SlAiSingleton<T>::Initialize()
{
	if (!TInstance.IsValid())
	{
		TInstance=Create();
	}
	
}

template <class T>
TSharedRef<T> SlAiSingleton<T>::Create()
{
	TSharedRef<T> TRef =MakeShareable(new T());
	return TRef;
}
