// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlAiEnemyCharacter.generated.h"

UCLASS()
class SLAI_API ASlAiEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlAiEnemyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	//武器插槽
	UPROPERTY(VisibleDefaultsOnly,Category=Mesh)
	class UChildActorComponent* WeaponSocket;
	//盾牌插槽
	UPROPERTY(VisibleDefaultsOnly,Category=Mesh)
	class UChildActorComponent* SheildSocket;
};
