// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
	
public:
	AInfiniteTerrainGameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Setup)
	UActorPool* NavPool = nullptr;

private:
	void AddToPool(ANavMeshBoundsVolume*);

	
};
