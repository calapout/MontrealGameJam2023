// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "EnhancedPlayerInput.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArm->SetupAttachment(GetMesh());
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	camera->AttachToComponent(springArm, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector2d normalizedVector = this->direction.GetSafeNormal();
	AddMovementInput(FVector3d(normalizedVector.X, normalizedVector.Y, 0), this->movementSpeed, false);
	GetRootComponent()->SetRelativeRotation(FRotator3f(0, 0, rotationX));
	camera->GetComponentTransform().TransformRotation(UE::Math::TQuat<double>());
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* input  = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	input->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move); //When moving
	input->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move); //When moving
	input->BindAction(this->MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move); //When moving
}

/** Returns the owning ULocalPlayer of an Enhanced Player Input pointer */
ULocalPlayer* AMainCharacter::GetLocalPlayer(const UEnhancedPlayerInput* PlayerInput)
{
	if (PlayerInput)
	{
		// Getting the owning Player Controller can also be useful :) 
		if (APlayerController* PC = Cast<APlayerController>(PlayerInput->GetOuter()))
		{
			return Cast<ULocalPlayer>(PC->GetLocalPlayer());
		}
	}
	return nullptr;
}

void AMainCharacter::Move(const FInputActionValue& value)
{
	FVector2d tempDirection = value.Get<FVector2d>();
	this->direction = tempDirection;
}

void AMainCharacter::RotateX(const FInputActionValue& value)
{
	this->rotationX += value.Get<float>() * rotationXSpeed;
	this->rotationX = fmod(this->rotationX, 360.0f);
	if(this->rotationX < 0)
	{
		this->rotationX = 360.0f - this->rotationX;
	}
}

void AMainCharacter::RotateY(const FInputActionValue& value)
{
	this->rotationY += value.Get<float>() * rotationYSpeed;
	this->rotationY = fmod(this->rotationY, 360.0f);
	if(this->rotationY < 0)
	{
		this->rotationY = 360.0f - this->rotationY;
	}
}

