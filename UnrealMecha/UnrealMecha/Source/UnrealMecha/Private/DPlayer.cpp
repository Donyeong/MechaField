// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayer.h"

void ADPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AGLOG_S(Warning);

}

void ADPlayer::PossessedBy(AController* NewController)
{
	AGLOG_S(Warning);
	Super::PossessedBy(NewController);
}

// Sets default values
ADPlayer::ADPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

