// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SlAiEnemyCharacter.h"

#include "Components/CapsuleComponent.h"
#include "EnemyTool/SlAiEnemyTool.h"

// Sets default values
ASlAiEnemyCharacter::ASlAiEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//设置AI控制器
	AIControllerClass = ASlAiEnemyCharacter::StaticClass();
	//设置碰撞体属性文件
	GetCapsuleComponent()->SetCollisionProfileName(FName("EnemyProfile"));
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	//添加模型
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticEnemyMesh(TEXT("SkeletalMesh'/Game/Res/PolygonAdventure/Mannequin/Enemy/SkMesh/Enemy.Enemy'"));
	GetMesh()->SetSkeletalMesh(StaticEnemyMesh.Object);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionResponseToChannels(ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.0f,0.0f,-90.0f));
	GetMesh()->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0.0f,0.0f,-90.f)));

	//添加动画蓝图
	static ConstructorHelpers::FClassFinder<UAnimInstance> StaticEnemyAnim(TEXT("AnimBlueprint'/Game/Blueprint/Enemy/Enemy_Animation.Enemy_Animation_C'"));
	GetMesh()->AnimClass = StaticEnemyAnim.Class;
	
	//实例化插槽
	WeaponSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponSocket"));
	SheildSocket = CreateDefaultSubobject<UChildActorComponent>(TEXT("SheildSocket"));
}

// Called when the game starts or when spawned
void ASlAiEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//绑定插槽
	WeaponSocket->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("RHSocket"));
	SheildSocket->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,FName("LHSocket"));

	//给插槽添加物品
	WeaponSocket->SetChildActorClass(ASlAiEnemyTool::SpawnEnemyWeapon());
	SheildSocket->SetChildActorClass(ASlAiEnemyTool::SpawnEnemyShild());
}

// Called every frame
void ASlAiEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlAiEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

