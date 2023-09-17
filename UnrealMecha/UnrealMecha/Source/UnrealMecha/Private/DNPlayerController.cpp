// Fill out your copyright notice in the Description page of Project Settings.


#include "DNPlayerController.h"

void ADNPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AGLOG_S(Warning);
}

void ADNPlayerController::OnPossess(APawn* aPawn)
{
	AGLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void ADNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}
