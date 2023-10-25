// Fill out your copyright notice in the Description page of Project Settings.

#include "DNGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "DNPlayer.h"
#include "DNPlayerController.h"

ADNGameMode::ADNGameMode() {
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/DNPlayer_BP.DNPlayer_BP_C"));
	check(NULL != PlayerPawnBPClass.Class);
	DefaultPawnClass = PlayerPawnBPClass.Class;
	//DUtilHandle = FPlatformProcess::GetDllHandle(TEXT("DUtil.dll"));

	PlayerControllerClass = ADNPlayerController::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Log, TEXT("Create GameMode"));
	DDebug::Logger::getInstance().subscribe(std::bind(&ADNGameMode::OnLogging, this, std::placeholders::_1, std::placeholders::_2));
	logic_main.Init();
	logic_main.Start();
}
ADNGameMode::~ADNGameMode()
{
	DDebug::Logger::getInstance().clearHandler();
}
void ADNGameMode::PostLogin(APlayerController* NewPlayer)
{
	UE_LOG(LogTemp, Log, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Log, TEXT("PostLogin End"));
}

void ADNGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	logic_main.Update(DeltaTime);
}
void ADNGameMode::OnLogging(DDebug::Logger::Level _level, const char* _message)
{
    FString Message = FString(_message);
    switch (_level)
    {
    case DDebug::Logger::Level::INFO: 
        UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
        break;

    default:
        UE_LOG(LogTemp, Log, TEXT("%s"), *Message);
        break;
    }
}

