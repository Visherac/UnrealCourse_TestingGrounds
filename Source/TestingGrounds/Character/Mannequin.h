// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Mannequin.generated.h"

UCLASS()
class TESTINGGROUNDS_API AMannequin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void UnPossessed() override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<class APracticeGun> GunBlueprint;

	UFUNCTION(BlueprintCallable, Category = Firing)
	void PullTrigger();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	FName FPMeshGunSocket = "";

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	FName TPMeshGunSocket = "";


private:
	UPROPERTY(VisibleDefaultsOnly)
	class UCameraComponent* FPCamera = nullptr;
	
	UPROPERTY(VisibleDefaultsOnly)
	class USkeletalMeshComponent* FPMesh = nullptr;

	UPROPERTY(VisibleDefaultsOnly)
	class USceneComponent* FPCameraOffset = nullptr;

	
	UPROPERTY(VisibleAnywhere)
	class APracticeGun* Gun = nullptr;

	
};
