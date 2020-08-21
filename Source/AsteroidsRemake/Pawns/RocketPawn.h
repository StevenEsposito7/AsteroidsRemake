/*
Steven Esposito
8/21/2020
*/

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "RocketPawn.generated.h"


//class UCameraComponent;

/**
 * 
 */
UCLASS()
class ASTEROIDSREMAKE_API ARocketPawn : public APawnBase
{
	GENERATED_BODY()
	
public:

	ARocketPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void DestroyPawn() override;

	bool GetIsPlayerAlive();


private:

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	//	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float FrictionAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotateSpeed;

	float CurrentSpeed;

	FVector MoveDirection;
	FVector PreviousForward;
	FQuat RotationDirection;

	//APlayerController* PlayerControllerRef;
	//FHitResult TraceHitResult;

	bool bIsPlayerAlive = true;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();


protected:

	virtual void BeginPlay() override;

};