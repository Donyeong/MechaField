// Fill out your copyright notice in the Description page of Project Settings.


#include "DNGameMode.h"
#include "DNPlayer.h"
#include "DNPlayerController.h"
#include "../UnrealMecha.h"
ADNGameMode::ADNGameMode() {
	DefaultPawnClass = ADNPlayer::StaticClass();
	PlayerControllerClass = ADNPlayerController::StaticClass();
}

void ADNGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("PostLogin End"));
}
