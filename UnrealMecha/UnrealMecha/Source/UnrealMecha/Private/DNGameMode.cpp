// Fill out your copyright notice in the Description page of Project Settings.

#include "DNGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "DNPlayer.h"
#include "DNPlayerController.h"
#include "../UnrealMecha.h"
ADNGameMode::ADNGameMode() {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DNPlayer_BP.DNPlayer_BP_C"));
	check(NULL != PlayerPawnBPClass.Class);
	DefaultPawnClass = PlayerPawnBPClass.Class;
	
	PlayerControllerClass = ADNPlayerController::StaticClass();
}

void ADNGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("PostLogin End"));
}
