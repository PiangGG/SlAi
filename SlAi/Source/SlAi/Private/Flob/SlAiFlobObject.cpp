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
	
}

void ASlAiFlobObject::RenderTexture()
{
	TSharedPtr<ObjectAttribute> ObjectAttr=*SlAiDataHandle::Get()->ObjectAttrMap.Find(ObjectIndex);
	ObjectIconTex= LoadObject<UTexture>(NULL,*ObjectAttr->TextPath);
	ObjectIconDynamic->SetTextureParameterValue(FName("ObjectTex"),ObjectIconTex);
	BaseMesh->SetMaterial(0,ObjectIconDynamic);
}

// Called every frame
void ASlAiFlobObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	int DirYaw = Stream.RandRange(-180.0f,180.0f);
	FRotator ForcRot=FRotator(0.0f,DirYaw,0.0f);
	BoxCollison->AddForce((FVector(0.0f,0.0f,4.0f)-ForcRot.Vector())*60000) ;
}

