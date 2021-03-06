// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SlAiPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Data/SlAiDataHandle.h"
#include "Flob/SlAiFlobObject.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Hand/SlAiHandObject.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SlAiPackageManager.h"
#include "Player/SlAiPlayerController.h"
#include "Player/SlAiPlayerState.h"

// Sets default values
ASlAiPlayerCharacter::ASlAiPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//开始设置人物碰撞属性为PlayerProfile,下面骨骼就可以设置无碰撞
	GetCapsuleComponent()->SetCollisionProfileName(FName("PlayerProfile"));
	//添加第一人称骨骼模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshFirst(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/FirstPlayer/SkMesh/FirstPlayer.FirstPlayer'"));
	MeshFirst=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshFirst"));
	MeshFirst->SetSkeletalMesh(StaticMeshFirst.Object);
	MeshFirst->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	MeshFirst->bOnlyOwnerSee = true;
	MeshFirst->bCastDynamicShadow = false;//渲染影子
	MeshFirst->bReceivesDecals = false;
	MeshFirst->SetCollisionObjectType(ECC_Pawn);//设置碰撞
	MeshFirst->SetCollisionEnabled(ECollisionEnabled::NoCollision);//没有碰撞
	MeshFirst->SetCollisionResponseToChannels(ECR_Ignore);//
	MeshFirst->SetRelativeLocation(FVector(0.0f,0.0f,-95.0f));
	MeshFirst->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f,0.0f,-90.0f)));
	//更新频率衰落
	MeshFirst->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;//?
	MeshFirst->PrimaryComponentTick.TickGroup = TG_PrePhysics;//?
	//
	//获取第一人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimFirst(TEXT("AnimBlueprint'/Game/Blueprint/Player/FirstPlayer_Animation.FirstPlayer_Animation_C'"));
	MeshFirst->AnimClass = StaticAnimFirst.Class;
	//设置碰撞属性
	
	//给默认mesh添加骨骼模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticMeshThird(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Player/SkMesh/Player.Player'"));
	GetMesh()->SetSkeletalMesh(StaticMeshThird.Object);
	GetMesh()->bOnlyOwnerSee = true;
	GetMesh()->bReceivesDecals = false;//是否允许贴画跟其他物体发生反射
	GetMesh()->SetCollisionObjectType(ECC_Pawn);//设置碰撞
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);//没有碰撞
	GetMesh()->SetCollisionResponseToChannels(ECR_Ignore);//
	GetMesh()->SetRelativeLocation(FVector(0.0f,0.0f,-95.0f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f,0.0f,-90.0f)));

	//获取第三人称的动作蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticAnimThird(TEXT("AnimBlueprint'/Game/Blueprint/Player/ThirdPlayer_Animation.ThirdPlayer_Animation_C'"));
	GetMesh()->AnimClass = StaticAnimThird.Class;
	
	//摄像机手臂
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CamerBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->TargetOffset = FVector(0.0f,0.0f,60.0f);
	CameraBoom->bUsePawnControlRotation = true;//绑定Controller旋转

	//初始化相机
	ThirdCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdCamera"));
	ThirdCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	ThirdCamera->bUsePawnControlRotation= false;//设置第三人称相机不跟随控制器旋转

	FirstCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("FirstCamera"));
	FirstCamera->SetupAttachment((USceneComponent*)GetCapsuleComponent());
	FirstCamera->bUsePawnControlRotation= true;//设置第三人称相机不跟随控制器旋转
	FirstCamera->AddLocalOffset(FVector(0.0f,0.0f,60.f));

	//默认第三人称
	FirstCamera->SetActive(false);
	ThirdCamera->SetActive(true);
	//不显示第一人称模型
	GetMesh()->SetOwnerNoSee(false);
	MeshFirst->SetOwnerNoSee(true);

	HandObject=CreateDefaultSubobject<UChildActorComponent>(TEXT("HandObject"));
	
	//初始化参数
	BaseTurnRate = 45.0f;
	BaseLookUpRate=45.0f;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;//初始速度150.0f

	//初始为第三人称
	GameView=EGameViewMode::Third;
	//上半身动作无
	upperType= EUpperBody::None;
	
	IsAllowSwitch=true;

	IsInputLocaked=false;

	IsAttack=false;
}

// Called when the game starts or when spawned
void ASlAiPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//如果控制器指针为空,添加引用
	SPController=Cast<ASlAiPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	//把手持物品组件绑定到第三人称模型右手上
	HandObject->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("RHSocket"));
	//添加actor到hand组件
	HandObject->SetChildActorClass(ASlAiHandObject::SpawnHandObject(0));
	
}

// Called every frame
void ASlAiPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlAiPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ASlAiPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASlAiPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn",this,&ASlAiPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("TurnAtRoate",this,&ASlAiPlayerCharacter::TurnAtRoate);
	PlayerInputComponent->BindAxis("LookUpAtRate",this,&ASlAiPlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASlAiPlayerCharacter::OnStartJump);
	PlayerInputComponent->BindAction("Jump",IE_Released,this,&ASlAiPlayerCharacter::OnStopJump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this,&ASlAiPlayerCharacter::OnStartRun);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ASlAiPlayerCharacter::OnStopRun);
}

void ASlAiPlayerCharacter::ChangeView(EGameViewMode::Type NewGameView)
{
	GameView=NewGameView;
	switch (GameView)
	{
	case EGameViewMode::First:
		FirstCamera->SetActive(true);
		ThirdCamera->SetActive(false);
		MeshFirst->SetOwnerNoSee(false);
		GetMesh()->SetOwnerNoSee(true);
		//修改HandObject绑定的位置
		HandObject->AttachToComponent(MeshFirst,FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("RHSocket"));
		break;
	case EGameViewMode::Third:
		FirstCamera->SetActive(false);
		ThirdCamera->SetActive(true);
		MeshFirst->SetOwnerNoSee(true);
		GetMesh()->SetOwnerNoSee(false);
		//修改HandObject绑定的位置
		HandObject->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("RHSocket"));
		break;
	}
}

void ASlAiPlayerCharacter::ChangeHandObject(TSubclassOf<AActor> HandObjectClass)
{	
	//设置物品到HandObject
	HandObject->SetChildActorClass(HandObjectClass);
}

void ASlAiPlayerCharacter::ChangeHandObjectDetect(bool IsOpen)
{
	//获取手上物品
	ASlAiHandObject* HandObjectClass=Cast<ASlAiHandObject>(HandObject->GetChildActor());
	if (HandObjectClass)HandObjectClass->ChangeOverlayDetect(IsOpen);

	IsAttack = IsOpen;
}

void ASlAiPlayerCharacter::RenderHandObject(bool IsRender)
{
	//如果手上物品没有
	if (!HandObject->GetChildActor())return;
	//如果有物品
	HandObject->GetChildActor()->SetActorHiddenInGame(!IsRender);
}

void ASlAiPlayerCharacter::PlayerThrowObject(int ObjectID, int Num)
{
	if (GetWorld())
	{
		for (int i=0;i<Num;++i)
		{
			//生成掉落資源
			ASlAiFlobObject* FlobObject = GetWorld()->SpawnActor<ASlAiFlobObject>
			(GetActorLocation()+FVector(0.0f,0.0f,40.0f),FRotator::ZeroRotator);
			FlobObject->ThrowFlobObject(ObjectID,GetActorRotation().Yaw);
		}
	}
}

bool ASlAiPlayerCharacter::IsPackageFree(int ObjectID)
{
	return SlAiPackageManager::Get()->SearchFreeSpace(ObjectID);
}

void ASlAiPlayerCharacter::AddPackageObject(int ObjectID)
{
	SlAiPackageManager::Get()->AddObject(ObjectID);
}

void ASlAiPlayerCharacter::EatUpEvent()
{
	//
	if(!SPController->SPState)return;
	//告诉背包哪个快捷栏被吃了,如果成功吃掉东西
	if (SlAiPackageManager::Get()->EatUpEvent(SPController->SPState->CurrentShortcutInfoIndex))
	{
		SPController->SPState->ProomoteHunger();
	}
}

bool ASlAiPlayerCharacter::IsPlayerDead()
{
	if(SPController->SPState)return SPController->SPState->IsPlayerDead();
	return  false;
}

void ASlAiPlayerCharacter::AcceptDamage(int Damage)
{
	if(SPController->SPState)SPController->SPState->AcceptDamage(Damage);
}

FVector ASlAiPlayerCharacter::GetCameraPos()
{
	switch (GameView)
	{
		case EGameViewMode::First:return  FirstCamera->K2_GetComponentLocation();
		case EGameViewMode::Third:return ThirdCamera->K2_GetComponentLocation();
	}
	return ThirdCamera->K2_GetComponentLocation();
}

void ASlAiPlayerCharacter::MoveForward(float value)
{
	if (IsInputLocaked)return;
	
	if (value!=0&&Controller)
	{
		const FRotator Rotation = Controller->GetDesiredRotation();
		FVector Dirction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Dirction,value);
	}
}

void ASlAiPlayerCharacter::MoveRight(float value)
{
	if (IsInputLocaked)return;
	if (value!=0)
	{
		const FQuat Rotation = GetActorQuat();
        FVector Dirction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
        AddMovementInput(Dirction,value);
	}
	
}

void ASlAiPlayerCharacter::LookUpAtRate(float value)
{
	if (IsInputLocaked)return;
	AddControllerPitchInput(value* BaseLookUpRate *GetWorld()->GetDeltaSeconds());
}

void ASlAiPlayerCharacter::Turn(float value)
{
	if (IsInputLocaked)return;
	AddControllerYawInput(value);
}

void ASlAiPlayerCharacter::TurnAtRoate(float value)
{
	if (IsInputLocaked)return;
	AddControllerYawInput(value* BaseTurnRate *GetWorld()->GetDeltaSeconds());
}

void ASlAiPlayerCharacter::OnStartJump()
{
	if (IsInputLocaked)return;
	bPressedJump=true;
}

void ASlAiPlayerCharacter::OnStopJump()
{
	if (IsInputLocaked)return;
	bPressedJump=false;
	StopJumping();
}

void ASlAiPlayerCharacter::OnStartRun()
{
	if (IsInputLocaked)return;
	GetCharacterMovement()->MaxWalkSpeed = 375.0f;
}

void ASlAiPlayerCharacter::OnStopRun()
{
	if (IsInputLocaked)return;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
}

