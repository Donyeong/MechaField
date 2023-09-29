// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DGenericLib/Containers.h"
#include "DNGameMode.generated.h"
/**
 * 
 */
UCLASS()
class UNREALMECHA_API ADNGameMode : public AGameMode
{
	GENERATED_BODY()
	ADNGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
