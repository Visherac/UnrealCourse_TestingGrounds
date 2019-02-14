// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextPatrolPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	
	UE_LOG(LogTemp, Warning, TEXT("Testing Code"))
	return EBTNodeResult::Succeeded;
}
