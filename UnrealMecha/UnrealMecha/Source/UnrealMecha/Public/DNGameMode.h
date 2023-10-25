// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../UnrealMecha.h"
#include "DGameLogic/Framework/LogicMain.h"
#include "DNGameMode.generated.h"
/**
 * 
 */
UCLASS()
class UNREALMECHA_API ADNGameMode : public AGameMode
{
	GENERATED_BODY()

	ADNGameMode();
	~ADNGameMode();
	virtual void PostLogin(APlayerController* NewPlayer) override;
public:
	virtual void Tick(float DeltaTime) override;
	void OnLogging(DDebug::Logger::Level _level, const char* _message);
	DLogic::LogicMain logic_main;
};
