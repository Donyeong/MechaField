// Fill out your copyright notice in the Description page of Project Settings.


#include "DNPlayer.h"
#include "MyAnimInstance.h"
// Sets default values
ADNPlayer::ADNPlayer()
{
	move_dir = FVector::Zero();
	//Property 기본 값 세팅
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

	float CameraYaw = Camera->GetComponentRotation().Yaw;
	FVector ForwardDirection = FVector(FMath::Cos(FMath::DegreesToRadians(CameraYaw)), FMath::Sin(FMath::DegreesToRadians(CameraYaw)), 0.0f);
	move_dir = ForwardDirection * move_dir.X + ForwardDirection.RotateAngleAxis(90, FVector::UpVector) * move_dir.Y;
	OnMove(move_dir);
	UpdateAnimation();
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (PC->IsInputKeyDown(EKeys::SpaceBar))
		{
			Dash();
		}
	}
	DashTick();
	bIsMoving = false;
}

// Called to bind functionality to input
void ADNPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &ADNPlayer::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &ADNPlayer::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Attack"), this, &ADNPlayer::Attack);
}

void ADNPlayer::UpDown(float NewAxisValue)
{
	//AGLOG(Warning, TEXT("UpDown %f"), NewAxisValue);
	move_dir.X = NewAxisValue;
}

void ADNPlayer::LeftRight(float NewAxisValue)
{
	//AGLOG(Warning, TEXT("LeftRight %f"), NewAxisValue);
	move_dir.Y = NewAxisValue;
}

void ADNPlayer::OnMove(FVector _direction)
{
	if (_direction.IsZero()) {
		return;
	}
	if (!dash_vector.IsZero()) {
		return;
	}

	FRotator rot = _direction.Rotation() + FRotator(0.0f, -90.0f, 0.0f);
	FRotator CurrentRotation = Mesh->GetComponentToWorld().GetRotation().Rotator();
	float InterpSpeed = 15.0f;
	FRotator trot = FMath::Lerp(CurrentRotation, rot, InterpSpeed * GetWorld()->GetDeltaSeconds());
	Mesh->SetWorldRotation(trot);
	AddMovementInput(_direction);
	bIsMoving = true;
}

void ADNPlayer::DashTick()
{
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + dash_vector;
	//SetActorLocation(EndLocation, true);
	FHitResult Hit(1.f);
	Movement->SafeMoveUpdatedComponent(dash_vector, GetActorRotation(), true, Hit);

	if (Hit.IsValidBlockingHit())
	{
		Movement->HandleImpact(Hit, GetWorld()->GetDeltaSeconds(), dash_vector);
		// Try to slide the remaining distance along the surface.
		Movement->SlideAlongSurface(dash_vector, 1.f - Hit.Time, Hit.Normal, Hit, true);
	}
	float InterpSpeed = 15.0f;
	dash_vector = FMath::VInterpTo(dash_vector, FVector::Zero(), GetWorld()->GetDeltaSeconds(), InterpSpeed);
	if (dash_vector.Size() < dash_stop) {
		dash_vector = FVector::Zero();
	}
}

void ADNPlayer::UpdateAnimation()
{
	UMyAnimInstance* AnimInstance = Cast<UMyAnimInstance>(Mesh->GetAnimInstance());
	AnimInstance->isWalking = bIsMoving || !dash_vector.IsZero();
}

void ADNPlayer::Attack(float NewAxisValue)
{

}

void ADNPlayer::Dash()
{
	if (!dash_vector.IsZero()) {
		return;
	}
	FVector DashDirection = move_dir;
	DashDirection.Normalize();
	dash_vector = DashDirection * dash_power;
}

void ADNPlayer::StopDash()
{
	dash_vector = FVector::Zero();
}