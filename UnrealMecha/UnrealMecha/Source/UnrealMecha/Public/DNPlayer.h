// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DNBasePawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "DNPlayer.generated.h"

UCLASS()
class UNREALMECHA_API ADNPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADNPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(VisibleAnywhere, Category = Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, Category = Visual)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UFloatingPawnMovement* Movement;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float camera_distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float camera_rotate_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float camera_rotate_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float camera_rotate_z;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TSubclassOf<UAnimInstance> PlayerAnim_BP;

	UPROPERTY(EditAnywhere, Category = Stat)
	float dash_power;
	UPROPERTY(EditAnywhere, Category = Stat)
	float dash_stop;
	UPROPERTY()
	bool bIsMoving;
	UPROPERTY()
	FVector move_dir;
	UPROPERTY()
	FVector dash_vector;
private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void OnMove(FVector _direction);
	void DashTick();
	void Dash();
	void StopDash();
	void UpdateAnimation();
	void Attack(float NewAxisValue);
};
