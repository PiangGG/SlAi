// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/SlAiEnemyController.h"

#include "AI/SlAiEnemyBlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Enemy/SlAiEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Player/SlAiPlayerCharacter.h"

ASlAiEnemyController::ASlAiEnemyController()
{
	PrimaryActorTick.bCanEverTick=true;
	
}

void ASlAiEnemyController::OnPossess(APawn* InPawn)
{
	//绝对一定要调用父类函数
	Super::OnPossess(InPawn);

	//顺便实例化一下角色
	SECharacter = Cast<ASlAiEnemyCharacter>(InPawn);

	//获取行为树资源
	UBehaviorTree* StaticBehaviorTreeObject = LoadObject<UBehaviorTree>(NULL,TEXT("BehaviorTree'/Game/Blueprint/Enemy/EnemyBehaviorTree.EnemyBehaviorTree'"));

	//直接绑定Controller，放入多个敌人AI会报错
	UBehaviorTree* BehaviorTreeObject = DuplicateObject<UBehaviorTree>(StaticBehaviorTreeObject,NULL);

	//如果资源不存在return
	if (!BehaviorTreeObject)return;
	
	//绑定Controller
	BehaviorTreeObject->BlackboardAsset = DuplicateObject<USlAiEnemyBlackboardData>((USlAiEnemyBlackboardData*)StaticBehaviorTreeObject->BlackboardAsset,NULL);;

	BlackboardComp=Blackboard;

	bool IsSuccess = true;
	if (BehaviorTreeObject->BlackboardAsset &&(Blackboard == nullptr||Blackboard->IsCompatibleWith(BehaviorTreeObject->BlackboardAsset)==false))
	{
		IsSuccess =	UseBlackboard(BehaviorTreeObject->BlackboardAsset,BlackboardComp);
	}

	if (IsSuccess)
	{
		BehaviorTreeComp = Cast<UBehaviorTreeComponent>(BrainComponent);

		if (!BehaviorTreeComp)
		{
			BehaviorTreeComp = NewObject<UBehaviorTreeComponent>(this,TEXT("BehaviorTreeComp"));
			BehaviorTreeComp->RegisterComponent();
		}
		BrainComponent=BehaviorTreeComp;
		check(BehaviorTreeComp!=NULL);
		//BehaviorTreeComp->StartTree(*BehaviorTreeObject,EBTExecutionMode::Looped);

		//设置状态为巡逻
		BlackboardComp->SetValueAsEnum("EnemyState",(uint8)EEnemyAIState::ES_Patrol);
		/*int32 EnemyStateIndex = BlackboardComp->GetKeyID("EnemyState");
		BlackboardComp->SetValue<UBlackboardKeyType_Enum>(EnemyStateIndex,(UBlackboardKeyType_Enum::FDataType)EEnemyAIState::ES_Patrol);*/

		//修改敌人初始速度是100
		SECharacter->SetMaxSpeed(100.0f);
	}
	//RunBehaviorTree();
}

void ASlAiEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
	//停止行为树
	if (BehaviorTreeComp) BehaviorTreeComp->StopTree();
}

void ASlAiEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//如果玩家指针和角色指针存在，一直修改角色朝向
	//if (SECharacter&&SPCharacter)SECharacter-
	//if (SECharacter&&SPCharacter) SECharacter->UpdateHPBarRotation(SPCharacter->GetCameraPos());
	
}

FVector ASlAiEnemyController::GetPlayerLocation() const
{
	if (SPCharacter) return SPCharacter->GetActorLocation();
	return FVector::ZeroVector;
}

bool ASlAiEnemyController::IsPlayerDead()
{
	if (SPCharacter) return SPCharacter->IsPlayerDead();
	return false;
}

void ASlAiEnemyController::OnSeePlayer()
{
	//如果已经锁定了玩家或者玩家死亡，不再执行下面行动
	if (IsLockPlayer || IsPlayerDead()) return;
	//设置锁定玩家
	IsLockPlayer = true;
	//修改预状态为追逐
	BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Chase);
	//修改敌人速度
	SECharacter->SetMaxSpeed(300.f);
}

void ASlAiEnemyController::LoosePlayer()
{
	//设置丢失玩家的锁定
	IsLockPlayer = false;
}

bool ASlAiEnemyController::IsPlayerAway()
{
	if (!IsLockPlayer || !SPCharacter || EPDisList.Num() < 6 || IsPlayerDead()) return false;
	int BiggerNum = 0;
	float LastDis = -1.f;
	//只要有三个比前面的大,就判定远离了
	for (TArray<float>::TIterator It(EPDisList); It; ++It)
	{
		if (*It > LastDis) BiggerNum += 1;
		LastDis = *It;
	}
	return BiggerNum > 3;
}

/*void ASlAiEnemyController::UpdateStatePama()
{
	if (EPDisList.Num()<6)
	{
		EPDisList.Push(FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation()));
	}
	else
	{
		EPDisList.RemoveAt(0);
		EPDisList.Push(FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation()));
	}
	//更新受伤害序列,受伤一次后6秒内不允许进入受伤状态
	if (HurtTimeCount < 6.f)
	{
		HurtTimeCount += 0.3f;
	}
	else {
		HurtTimeCount = 0.f;
		IsAllowHurt = true;
	}
}*/

UObject* ASlAiEnemyController::GetPlayerPawn()
{
	return SPCharacter;
}

void ASlAiEnemyController::ResetProcess(bool IsFinish)
{
	//修改完成状态
	BlackboardComp->SetValueAsBool("ProcessFinish", IsFinish);
}

void ASlAiEnemyController::UpdateDamageRatio(float HPRatioVal)
{
	//更新血值百分比
	HPRatio = HPRatioVal;
	//状态修改为受伤
	if(IsAllowHurt) BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Hurt);
	//设置允许受伤状态
	IsAllowHurt = false;
}

void ASlAiEnemyController::FinishStateHurt()
{
	//如果没有锁定玩家,设置锁定
	if (!IsLockPlayer) IsLockPlayer = true;
	//如果血值在0.2f以下
	if (HPRatio<0.2f)
	{
		//创建随机流
		FRandomStream Stream;
		//产生新的随机种子
		Stream.GenerateNewSeed();
		//先随机一个动作类别
		int ActionRatio = Stream.RandRange(0, 10);
		//30%的几率触发防御
		if (ActionRatio<4)
		{
			//进入防御状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else {
			//进入逃跑
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
	}
	else
	{
		//创建随机流
		FRandomStream Stream;
		//产生新的随机种子
		Stream.GenerateNewSeed();
		//先随机一个动作类别
		int ActionRatio = Stream.RandRange(0, 10);
		//30的几率触发防御
		if (ActionRatio < 4) {
			//进入防御状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
		}
		else
		{
			//进入攻击
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}
}

void ASlAiEnemyController::FinishStateDefence()
{
	/*//设置状态完成
	ResetProcess(true);
	//停止防御动作
	SECharacter->StopDefence();
	//获取与玩家的距离
	float SEToSP = FVector::Distance(SECharacter->GetActorLocation(), GetPlayerLocation());
	//如果玩家还在攻击并且距离小于200,继续防御状态
	if (SEToSP<200.f&&SPCharacter->IsAttack)
	{
		BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Defence);
	}
	else
	{
		//如果血值小于0.2,逃跑
		if (HPRatio < 0.2f)
		{
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Escape);
		}
		else
		{
			//跳到攻击状态
			BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Attack);
		}
	}*/
}

void ASlAiEnemyController::EnemyDead()
{
	//停止行为树
	if (BehaviorTreeComp) BehaviorTreeComp->StopTree(EBTStopMode::Safe);
	//临时代码，注销时间函数
	if (EPDisHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(EPDisHandle);
}

void ASlAiEnemyController::BeginPlay()
{
	//绝对调用父类函数
	Super::BeginPlay();
	//初始化玩家指针，这个指针会一直在
	SPCharacter=Cast<ASlAiPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GWorld,0));
	//如果角色没有初始化
	if(!SECharacter)SECharacter = Cast<ASlAiEnemyCharacter>(GetPawn());

	//初始设定没有锁定玩家
	IsLockPlayer = false;
	/*//绑定定时器
	FTimerDelegate EPDisDele = FTimerDelegate::CreateUObject(this, &ASlAiEnemyController::UpdateStatePama);
	GetWorld()->GetTimerManager().SetTimer(EPDisHandle, EPDisDele, 0.3f, true);

	//血量初始化为1
	HPRatio = 1;

	//设置状态计时器
	IsAllowHurt = false;
	HurtTimeCount = 0.f;
	*/
}

void ASlAiEnemyController::UpdateStatePama()
{
	//更新血值百分比
	//HPRatio = HPRatioVal;
	//状态修改为受伤
	if(IsAllowHurt) BlackboardComp->SetValueAsEnum("EnemyState", (uint8)EEnemyAIState::ES_Hurt);
	//设置允许受伤状态
	IsAllowHurt = false;
}
