// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPackageManager.h"

#include "Common/SlAiHelper.h"

TSharedPtr<SlAiPackageManager> SlAiPackageManager::PackageInstance = NULL;
SlAiPackageManager::SlAiPackageManager()
{
	//初始化
	ObjectIndex = 3;
	ObjectNum = 35;
}

void SlAiPackageManager::Initialize()
{
	if (!PackageInstance.IsValid())
	{
		PackageInstance=Create();
	}
}

TSharedPtr<SlAiPackageManager> SlAiPackageManager::Get()
{
	Initialize();
	return PackageInstance;
}

void SlAiPackageManager::InsertContainer(TSharedPtr<SSlAiContainerBaseWidget> Container, EContainerType::Type InsertType)
{
	switch (InsertType)
	{
	case EContainerType::Output:
		OutputContainer = Container;
		OutputContainer->CompoundOutput.BindRaw(this,&SlAiPackageManager::Compoundoutput);
		OutputContainer->ThrowObject.BindRaw(this,&SlAiPackageManager::ThrowObject);
		break;
	case EContainerType::Input:
		Container->CompoundInput.BindRaw(this,&SlAiPackageManager::CompoundInput);
		Container->CompoundInput.BindRaw(this, &SlAiPackageManager::CompoundInput);
		InputContainerList.Add(Container);
		break;
	case EContainerType::Normal:
		NormalContainerList.Add(Container);
		break;
	case EContainerType::Shortcut:
		Container->PackShortChange.BindRaw(this,&SlAiPackageManager::PackShortChange);
		ShortcutContainerList.Add(Container);
		break;
	}
}

void SlAiPackageManager::UpdateHovered(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取悬停的容器
	SlAiHelper::Debug(MousePos.ToString(),0.f);
	TSharedPtr<SSlAiContainerBaseWidget> CurrHoveredCon = LocateContainer(MousePos, PackGeo);
	//如果容器存在
	if (CurrHoveredCon.IsValid())
	{
		//设置当前容器悬停显示
		CurrHoveredCon->UpdateHovered(true);
		//如果上一容器存在，并且与当前容器不相同
		if (LastHoveredCon.IsValid() && LastHoveredCon.Get() != CurrHoveredCon.Get())
		{
			//更新悬停显示
			LastHoveredCon->UpdateHovered(false);
		}
	}
	else
	{
		//当前容器不存在且上一容器存在，取消上一容器的悬停显示
		if (LastHoveredCon.IsValid())
		{
			LastHoveredCon->UpdateHovered(false);
		}
	}
	
	//更新上一悬停容器
	LastHoveredCon = CurrHoveredCon;
}

void SlAiPackageManager::LeftOption(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取点击的容器
	TSharedPtr<SSlAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos,PackGeo);
	//如果容器存在，执行容器事件
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->LeftOperate(ObjectIndex,ObjectNum,ObjectIndex,ObjectNum);
	}
	//如果容器不存在并且手上物品不为空
	if (!ClickedContainer.IsValid()&&ObjectIndex!=0)
	{
		//把物品丢弃
		ThrowObject(ObjectIndex,ObjectNum);
		//重置物品
		ObjectIndex = ObjectNum = 0;
		
	}
}

void SlAiPackageManager::RightOption(FVector2D MousePos, FGeometry PackGeo)
{
	//先获取点击的容器
	TSharedPtr<SSlAiContainerBaseWidget> ClickedContainer = LocateContainer(MousePos,PackGeo);
	//如果容器存在，执行容器事件
	if (ClickedContainer.IsValid())
	{
		ClickedContainer->RightOperate(ObjectIndex,ObjectNum,ObjectIndex,ObjectNum);
	}
}

TSharedRef<SlAiPackageManager> SlAiPackageManager::Create()
{
	TSharedRef<SlAiPackageManager> PackageRef=MakeShareable(new SlAiPackageManager());
	return PackageRef;
}

TSharedPtr<SSlAiContainerBaseWidget> SlAiPackageManager::LocateContainer(FVector2D MousePos, FGeometry PackGeo)
{
	//迭代找到指向的容器
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(ShortcutContainerList); It; ++It)
	{
		//获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);

		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);

		//判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)
		{
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(NormalContainerList); It; ++It)
	{
		//获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		//判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	for (TArray<TSharedPtr<SSlAiContainerBaseWidget>>::TIterator It(InputContainerList); It; ++It)
	{
		//获取区域
		FVector2D StartPos = PackGeo.AbsoluteToLocal((*It)->GetCachedGeometry().AbsolutePosition);
		FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
		//判断鼠标位置是否在区域内,在的话直接返回这个容器
		if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y) {
			return *It;
		}
	}
	//这里处理输出容器的
	//获取区域
	FVector2D StartPos = PackGeo.AbsoluteToLocal(OutputContainer->GetCachedGeometry().AbsolutePosition);
	
	FVector2D EndPos = StartPos + FVector2D(80.f, 80.f);
	//判断鼠标位置是否在区域内,在的话直接返回这个容器
	if (MousePos.X >= StartPos.X && MousePos.X <= EndPos.X && MousePos.Y >= StartPos.Y && MousePos.Y <= EndPos.Y)
	{
		SlAiHelper::Debug(StartPos.ToString(),0.f);
		return OutputContainer;
	}
	//最后返回空
	return nullptr;
}

void SlAiPackageManager::ThrowObject(int ObjectID, int Num)
{
	PlayerThrowObject.ExecuteIfBound(ObjectID,Num);
}

void SlAiPackageManager::Compoundoutput(int ObjectID, int Num)
{
}

void SlAiPackageManager::CompoundInput()
{
}

void SlAiPackageManager::PackShortChange(int ShortcutID, int ObjectID, int ObjectNumber)
{
	//执行委托,绑定的方法是PlayerState的ChangeHandObject,在playercharacter下进行绑定
	ChangeHandObject.ExecuteIfBound(ShortcutID, ObjectID, ObjectNumber);
}
