// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolComponent.h"

EBTNodeResult::Type UChooseNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//get patrol points
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolComponent = Pawn->FindComponentByClass<UPatrolComponent>();

	if (!ensure(PatrolComponent)) { return EBTNodeResult::Failed; }
	
	auto PatrolPoints = PatrolComponent->GetPatrolPoints();

	if (PatrolPoints.Num() <= 0) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("%s is missing a Patrol Point assignments."), *Pawn->GetName())
		return EBTNodeResult::Failed; 
	}

	//get next control point
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto NextPatrolPoint = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(PatrolPointKey.SelectedKeyName, NextPatrolPoint);

	//increment index
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
	
}
