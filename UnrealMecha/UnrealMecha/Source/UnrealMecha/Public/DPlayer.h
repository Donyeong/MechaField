// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UnrealMecha.h"
#include "GameFramework/Character.h"
#include "DPlayer.generated.h"

UCLASS()
class UNREALMECHA_API ADPlayer : public ACharacter
{
	GENERATED_BODY()
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

public:
	// Sets default values for this character's properties
	ADPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
