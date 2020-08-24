/*
Steven Esposito
8/21/2020
*/

#include "RocketPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
//#include "Camera/CameraComponent.h"

ARocketPawn::ARocketPawn()
{
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	MoveSpeed = 200.0f;
	FrictionAmount = 0.5f;
	RotateSpeed = 50.0f;
	CurrentSpeed = 0.0f;
}

void ARocketPawn::BeginPlay()
{
	Super::BeginPlay();

	//PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ARocketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

	//UE_LOG(LogTemp, Warning, TEXT("Forward Vector: %f, %f, %f"), GetActorForwardVector().X, GetActorForwardVector().Y, GetActorForwardVector().Z);
}

void ARocketPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARocketPawn::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &ARocketPawn::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARocketPawn::Fire);
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARocketPawn::Fire);
}

void ARocketPawn::CalculateMoveInput(float Value)
{
	// Give player rocket momentum if MoveForward input is not pressed and CurrentSpeed is not depleted fully by FrictionAmount 
	if (Value > 0.0f)
	{
		CurrentSpeed = MoveSpeed;
		PreviousForward = GetActorForwardVector();
	}
	else if (CurrentSpeed > 0.0f)
	{
		CurrentSpeed -= FrictionAmount;
		Value = 1.0f;
		FMath::Clamp(CurrentSpeed, 0.0f, MoveSpeed);
	}

	MoveDirection = PreviousForward * Value * CurrentSpeed * GetWorld()->DeltaTimeSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), MoveDirection.X, MoveDirection.Y, MoveDirection.Z);
}

void ARocketPawn::CalculateRotateInput(float Value)
{
	float RotateAmount = Value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);
}

void ARocketPawn::Move()
{
	SetActorLocation(GetActorLocation() + MoveDirection);
	//MeshComp->AddForce(MoveDirection * MoveSpeed * MeshComp->GetMass());
}

void ARocketPawn::Rotate()
{
	AddActorLocalRotation(RotationDirection, true);
	//MeshComp->AddTorque(FVector(0.0f, 0.0f, 1.0f) * RotateSpeed * MeshComp->GetMass());
}

void ARocketPawn::DestroyPawn()
{
	Super::DestroyPawn();

	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool ARocketPawn::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}