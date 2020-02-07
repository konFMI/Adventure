// Fill out your copyright notice in the Description page of Project Settings.


#include "Batka.h"
#include <Runtime\Engine\Classes\Engine\Engine.h>
#include "Components\InputComponent.h"
#include "GameFramework\Controller.h"
#include "Camera\CameraComponent.h"
#include "Components\SkeletalMeshComponent.h"
#include "Components\ArrowComponent.h"
#include "Components\CapsuleComponent.h"
#include "Projectile.h"



// Sets default values
ABatka::ABatka()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	// Create first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//Possition the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f) + BaseEyeHeight);
	// Attach the camera component to out capsule component.
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	// Allow the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	/*
	 //Create a first person mesh component for the owning player.
	BatkaMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonBatkaMesh"));
	// Only the owning player sees this mesh.
	BatkaMesh->SetOnlyOwnerSee(true);
	// Attack fps mesh to fps camera.
	BatkaMesh->SetupAttachment(FPSCameraComponent);
	// Dissable some environmental shadowin to preserve the illusion of having a single mesh.
	BatkaMesh->bCastDynamicShadow = false;
	BatkaMesh->CastShadow = false;

	GetMesh()->SetOwnerNoSee(true);
	*/
}

// Called when the game starts or when spawned
void ABatka::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using Batka."));
	}
	
}

// Called every frame
void ABatka::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABatka::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &ABatka::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABatka::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &ABatka::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABatka::AddControllerPitchInput);

	//Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABatka::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABatka::StopJump);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABatka::Fire);

	
}

void ABatka::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ABatka::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ABatka::StartJump()
{
	bPressedJump = true;
}

void ABatka::StopJump()
{
	bPressedJump = false;
}

void ABatka::Fire()
{
	if (ProjectileClass)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;

		GetActorEyesViewPoint(CameraLocation, CameraRotation);


		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;

		// Skew the aim to be slightly upwards.
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();

		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			// Spawn the projectile at the muzzle.
			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Set the projectile's initial trajectory.
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

