// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChooseNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API UChooseNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


protected:
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector IndexKey;
	
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector PatrolPointKey;
	
};
