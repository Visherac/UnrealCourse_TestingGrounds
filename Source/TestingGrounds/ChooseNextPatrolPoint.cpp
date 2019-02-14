// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "public/PatrollingGuard.h"
#include "AIController.h"

EBTNodeResult::Type UChooseNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	//get patrol points
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Pawn = Cast<APatrollingGuard>(OwnerComp.GetAIOwner()->GetPawn());
	auto PatrolPoints = Pawn->PatrolPointsCPP;
	
	//get next control point
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto NextPatrolPoint = PatrolPoints[Index];
	BlackboardComp->SetValueAsObject(PatrolPointKey.SelectedKeyName, NextPatrolPoint);
	
	//increment index
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);
	
	return EBTNodeResult::Succeeded;
}
