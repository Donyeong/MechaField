// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../UnrealMecha.h"
#include "GameFramework/PlayerController.h"
#include "DNPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMECHA_API ADNPlayerController : public APlayerController
{
	GENERATED_BODY()
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;
};
