// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

/**
 * 
 */

class ANavMeshBoundsVolume;
class UActorPool

UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultOnly, BlueprintReadOnly, Category = Setup);
	UActorPool* NavPool = nullptr;

	UFUNCTION(BlueprintCallable)
	void PopulateBoundsVolumePool();

private:
	void AddToPool(ANavMeshBoundsVolume*);

	
};
