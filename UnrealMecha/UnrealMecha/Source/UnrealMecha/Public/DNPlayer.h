// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UnrealMecha.h"
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
private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
};
