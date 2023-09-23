// Fill out your copyright notice in the Description page of Project Settings.


#include "DNPlayer.h"
#include "MyAnimInstance.h"
// Sets default values
ADNPlayer::ADNPlayer()
{
	//Property 기본 값 세팅
	move_speed = 0.5f;
	camera_rotate_x = -60.0f;
	camera_rotate_y = 0.0f;
	camera_rotate_z = 0.0f;
	camera_distance = 200.0f;
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
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBP(TEXT("/Game/Animation/PlayerAni.PlayerAni_C"));
	if (AnimBP.Succeeded())
	{
		PlayerAnim_BP = AnimBP.Class;
	}
	AGCHECK(PlayerAnim_BP);
	Mesh->SetAnimInstanceClass(PlayerAnim_BP);
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

	UpdateAnimation();
	bIsMoving = false;
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
	if (NewAxisValue != 0) {
		AGLOG(Warning, TEXT("updown %f"), NewAxisValue);
		OnMove(GetActorForwardVector() * NewAxisValue);
	}
}

void ADNPlayer::LeftRight(float NewAxisValue)
{
	if (NewAxisValue != 0) {
		AGLOG(Warning, TEXT("leftright %f"), NewAxisValue);
		OnMove(GetActorRightVector() * NewAxisValue);
	}
}

void ADNPlayer::OnMove(FVector _direction)
{
	float CameraYaw = Camera->GetComponentRotation().Yaw;
	FVector ForwardDirection = FVector(FMath::Cos(FMath::DegreesToRadians(CameraYaw)), FMath::Sin(FMath::DegreesToRadians(CameraYaw)), 0.0f);
	FVector CombinedDirection = ForwardDirection * _direction.X + ForwardDirection.RotateAngleAxis(90, FVector::UpVector) * _direction.Y;

	FRotator rot = CombinedDirection.Rotation() + FRotator(0.0f, -90.0f, 0.0f);
	FRotator CurrentRotation = Mesh->GetComponentToWorld().GetRotation().Rotator();
	float InterpSpeed = 15.0f;
	FRotator trot = FMath::Lerp(CurrentRotation, rot, InterpSpeed * GetWorld()->GetDeltaSeconds());
	Mesh->SetWorldRotation(trot);
	AddMovementInput(CombinedDirection, move_speed);
	bIsMoving = true;
}

void ADNPlayer::UpdateAnimation()
{
	UMyAnimInstance* AnimInstance = Cast<UMyAnimInstance>(Mesh->GetAnimInstance());
	AnimInstance->isWalking = bIsMoving;
}