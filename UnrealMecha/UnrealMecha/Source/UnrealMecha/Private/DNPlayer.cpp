// Fill out your copyright notice in the Description page of Project Settings.


#include "DNPlayer.h"

// Sets default values
ADNPlayer::ADNPlayer()
{
	//Property 기본 값 세팅
	camera_rotate_x = -60.0f;
	camera_rotate_y = 0.0f;
	camera_rotate_z = 0.0f;
	camera_distance = 600.0f;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength = camera_distance;
	SpringArm->SetRelativeRotation(FRotator(camera_rotate_x, camera_rotate_y, camera_rotate_z));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/GameResource/SwG_IDLE_V2.SwG_IDLE_V2"));
	if (SK_CARDBOARD.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}
}

// Called when the game starts or when spawned
void ADNPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADNPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADNPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ADNPlayer::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ADNPlayer::LeftRight);

}

void ADNPlayer::UpDown(float NewAxisValue)
{
	AGLOG(Warning, TEXT("updown %f"), NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void ADNPlayer::LeftRight(float NewAxisValue)
{
	AGLOG(Warning, TEXT("leftright %f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue);
}

