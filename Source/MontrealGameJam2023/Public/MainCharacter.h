// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Math/Vector2D.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MONTREALGAMEJAM2023_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Expose a mapping context as a property in your header file...
	UPROPERTY(EditAnywhere, Category="Input")
	UInputMappingContext* InputMapping;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseXAxisAction;
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseYAxisAction;
	
	UPROPERTY(EditAnywhere)
	USpringArmComponent* springArm;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* camera;
	
	FVector2d direction = FVector2d::Zero();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float rotationX = 0;
	UPROPERTY(EditAnywhere, Category="Input")
	float rotationXSpeed = 0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float rotationY = 0;
	UPROPERTY(EditAnywhere, Category="Input")
	float rotationYSpeed = 0;

	// UPROPERTY(EditAnywhere, Category="Gameplay Values")
	float movementSpeed = 1.0;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	static ULocalPlayer* GetLocalPlayer(const UEnhancedPlayerInput* PlayerInput);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& value);
	void RotateX(const FInputActionValue& value);
	void RotateY(const FInputActionValue& value);
};
