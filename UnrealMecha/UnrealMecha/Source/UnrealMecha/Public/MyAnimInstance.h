// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EState : uint8 {
	Idle UMETA(DisplayName = "Idle")
};

UCLASS()
class UNREALMECHA_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	UMyAnimInstance();
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool isWalking = false;
	EState anim_state;

	
};

