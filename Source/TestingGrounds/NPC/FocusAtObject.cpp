// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusAtObject.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UFocusAtObject::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto AIController = OwnerComp.GetAIOwner();

	//get focus point
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto FocusObject = BlackboardComp->GetValueAsObject(FocusObjectKey.SelectedKeyName);
	
	if (!FocusObject)
	{
		//FocusObject is nullptr, don't focus on anything.
		AIController->ClearFocus(EAIFocusPriority::Default);

		UE_LOG(LogTemp, Warning, TEXT("Clearing Focus"))
	}
	else
	{
		auto FocusActor = Cast<AActor>(FocusObject);
		if (!ensure(FocusActor)){return EBTNodeResult::Failed;}

		AIController->SetFocus(FocusActor, EAIFocusPriority::Gameplay);
	}
	return EBTNodeResult::Succeeded;

}



