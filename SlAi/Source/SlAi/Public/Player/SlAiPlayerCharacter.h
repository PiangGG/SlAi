// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlAiPlayerCharacter.generated.h"

UCLASS()
class SLAI_API ASlAiPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlAiPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class UCameraComponent* ThirdCamera;
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	class UCameraComponent* FirstCamera;

private:
	void MoveForward(float value);
	void MoveRight(float value);
	void LookUpAtRate(float value);
	void Turn(float value);
	void TurnAtRoate(float value);
	void OnStartJump();
	void OnStopJump();
	void OnStartRun();
	void OnStopRun();
private:
	//第一人称骨骼模型
	UPROPERTY(VisibleDefaultsOnly,Category="SlAi")
	USkeletalMeshComponent* MeshFirst;

	//旋转比例
	float BaseLookUpRate;
	float BaseTurnRate;
};
