// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

FHitResult;

USTRUCT(BlueprintType)
struct FMeshDetails
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	UStaticMesh* DetailMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Setup)
	int32 NumInstances;

	FMeshDetails()
	{
		DetailMesh = nullptr;
		NumInstances = 0;
	}
};



UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawnCount =1, int32 MaxSpawnCount =1, float MinScaleValue =1.0f, float MaxScaleValue = 1.0f);
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TArray<FMeshDetails> DetailMeshes;

	UPROPERTY(VisibleDefaultsOnly)
	TArray<class UHierarchicalInstancedStaticMeshComponent*> DetailComponents;

	AActor* PlaceActor(TSubclassOf<AActor> ToSpawn, FVector Location, FRotator Rotation, float scale);

	FVector GetRandomLocation();

	bool FindEmptyLocation(FVector& OutLocation, float Radius, int32 MaxAttempts);

	bool IsValidLocation(FVector Location, float Radius);

};
