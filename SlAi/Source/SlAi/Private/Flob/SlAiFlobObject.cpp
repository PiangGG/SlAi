// Fill out your copyright notice in the Description page of Project Settings.


#include "Flob/SlAiFlobObject.h"

#include "Components/BoxComponent.h"
#include "Data/SlAiDataHandle.h"
#include "Data/SlAiTypes.h"

// Sets default values
ASlAiFlobObject::ASlAiFlobObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollison=CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollison"));
	RootComponent = (USceneComponent*)BoxCollison;
	BoxCollison->SetCollisionProfileName(FName("FlobProfile"));
	//启用物体模拟
	BoxCollison->SetSimulatePhysics(true);
	//锁定旋转
	BoxCollison->SetConstraintMode(EDOFMode::Default);
	BoxCollison->GetBodyInstance()->bLockXRotation = true;
	BoxCollison->GetBodyInstance()->bLockYRotation = true;
	BoxCollison->GetBodyInstance()->bLockZRotation = true;
	BoxCollison->SetBoxExtent(FVector(15.0f));//设置碰撞体大小
	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("Static'/Engine/BasicShapes/Plane.Plane'"));
	BaseMesh->SetStaticMesh(StaticMesh.Object);
	BaseMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//设置变换
	BaseMesh->SetRelativeRotation(FRotator(0.0f,0.0f,90.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.3f));

	UMaterialInterface* StaticObjectIconMat = LoadObject<UMaterialInstance>(NULL,TEXT("MaterialInstanceConstant'/Game/Material/FlobIconMatInst.FlobIconMatInst'"));
	//动态创建材质
	ObjectIconDynamic = UMaterialInstanceDynamic::Create(StaticObjectIconMat,nullptr);
	
}

// Called when the game starts or when spawned
void ASlAiFlobObject::BeginPlay()
{
	Super::BeginPlay();
	//检测世界是否存在
	if (!GetWorld())return;

	//注册检测事件
	FTimerDelegate DetectPlayerDele;
	DetectPlayerDele.BindUObject(this,&ASlAiFlobObject::DetectPlayer);
	//每秒运行一次，循环运行，延迟三秒运行
	GetWorld()->GetTimerManager().SetTimer(DeterctTimer,DetectPlayerDele,1.0f,true,3.0f);
	//注册销毁事件
	FTimerDelegate DestroyDele;
	DestroyDele.BindUObject(this,&ASlAiFlobObject::DestroyEvent);
	GetWorld()->GetTimerManager().SetTimer(DeterctTimer,DetectPlayerDele,30.0f,false,3.0f);
	SPCharacter=NULL;
}

void ASlAiFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr=*SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex= LoadObject<UTexture>(NULL,*ObjectAttr->TextPath);
	ObjectIconDynamic->SetTextureParameterValue(FName("ObjectTex"),ObjectIconTex);
	BaseMesh->SetMaterial(0,ObjectIconDynamic);
}

void ASlAiFlobObject::DetectPlayer()
{
	if (!GetWorld())return;
	
	//保存检测结果
	TArray<FOverlapResult> Overlaps;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	//检测世界是否存在
	if (GetWorld()->OverlapMultiByObjectType(Overlaps,GetActorLocation(),FQuat::Identity,ObjectParams,FCollisionShape::MakeSphere(200.0f),Params))
	{
		for (TArray<FOverlapResult>::TIterator It(Overlaps);It;++It)
		{
			//如果检测到玩家
			if (Cast<ASlAiPlayerCharacter>(It->GetActor()))
			{
				SPCharacter = Cast<ASlAiPlayerCharacter>(It->GetActor());
				if (SPCharacter)
				{
					//停止检测
					GetWorld()->GetTimerManager().PauseTimer(DeterctTimer);
					//停止销毁定时器
					GetWorld()->GetTimerManager().PauseTimer(DestroyTimer);
					//关闭物理模拟
					BoxCollison->SetSimulatePhysics(false);
				}
				return;
			}
		}		
	}
}

void ASlAiFlobObject::DestroyEvent()
{
	if (!GetWorld())return;;
	//注销定时器
	GetWorld()->GetTimerManager().ClearTimer(DeterctTimer);
	GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
	//销毁自己
	GetWorld()->DestroyActor(this);
}

// Called every frame
void ASlAiFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//一直旋转
	BaseMesh->AddLocalRotation(FRotator(DeltaTime*60.f,0.0,0.0f));
	//如果检测到玩家
	if (SPCharacter)	
	{
		//靠经玩家
		SetActorLocation(FMath::VInterpTo(GetActorLocation(),SPCharacter->GetActorLocation()+FVector(0.0f,0.0f,40.f),DeltaTime,5.0f));
		//如果距离接近0
		if(FVector::Distance(GetActorLocation(),SPCharacter->GetActorLocation()+FVector(0.0f,0.0f,40.0f))<10)
		{
			//判断玩家背包是否有空间
			if (true)
			{
				//添加对应物品到背包
				//销毁自己
				DestroyEvent();
			}else
			{
				//如果玩家背包不为空,重置参数
				SPCharacter = NULL;
				//唤醒检测
				GetWorld()->GetTimerManager().UnPauseTimer(DeterctTimer);
				//唤醒销毁线程
				GetWorld()->GetTimerManager().UnPauseTimer(DestroyTimer);
				//开启物理模拟
				BoxCollison->SetSimulatePhysics(true);	
			}
		}
		
	}
}

void ASlAiFlobObject::CreateFlobObject(int ObjectID)
{
	//指定ID
	ObjectIndex=ObjectID;
	//渲染贴图
	RenderTexture();
	//做随机方向力
	FRandomStream Stream;
	Stream.GenerateNewSeed();
	int DirYaw = Stream.RandRange(-180,180);
	FRotator ForcRot=FRotator(0.0f,DirYaw,0.0f);
	
	BoxCollison->AddForce((FVector(0.0f,0.0f,4.0f)+ForcRot.Vector())*100000.0f) ;
}

void ASlAiFlobObject::ThrowFlobObject(int ObjectID, float DirYaw)
{
	//指定ID
	ObjectIndex=ObjectID;
	//渲染贴图
	RenderTexture();
	//做随机方向力
	FRandomStream Stream;
	
	Stream.GenerateNewSeed();
	DirYaw+=Stream.RandRange(-30,30);
	FRotator ForcRot=FRotator(0.0f,DirYaw,0.0f);
	
	BoxCollison->AddForce((FVector(0.0f,0.0f,4.0f)+ForcRot.Vector())*120000.0f) ;
}

