// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "engine/World.h"
#include "Camera/CameraComponent.h"
#include "components/SceneComponent.h"
#include "components/SkeletalMeshComponent.h"
#include "../Weapons/PracticeGun.h"
#include "components/CapsuleComponent.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPCameraOffset = CreateDefaultSubobject<USceneComponent>(TEXT("FP Camera Offset"));
	FPCameraOffset->SetupAttachment(GetCapsuleComponent());
	FPCameraOffset->SetRelativeLocation(FVector(42.731846, 5.364887, 9.890884));

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FP Camera"));
	FPCamera->SetupAttachment(FPCameraOffset);
	FPCamera->SetRelativeLocation(FVector(-39.560001, 1.750000, 64.000000));
	FPCamera->bUsePawnControlRotation = true;

	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP Mesh"));
	FPMesh->SetupAttachment(FPCamera);
	FPMesh->SetRelativeLocation(FVector(3.293318, -4.998758, -161.327179));
	FPMesh->SetRelativeRotation(FRotator(1.900000, -19.190001, 5.200000));
	FPMesh->SetOnlyOwnerSee(true);
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(GunBlueprint))
	{
		Gun = GetWorld()->SpawnActor<APracticeGun>(GunBlueprint);
		Gun->AttachToComponent(FPMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FPMeshGunSocket);
		Gun->AnimInstance = FPMesh->GetAnimInstance();

		if (InputComponent != nullptr)
		{
			InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AMannequin::PullTrigger);
		}
	}



}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMannequin::PullTrigger()
{
	Gun->Fire();
}

