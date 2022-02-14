// Fill out your copyright notice in the Description page of Project Settings.

#include "SideDeneme/Public/Characters/MasterEnemyAI.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"

UBlackboardComponent* AMasterEnemyAI::GetBlackboard()
{
	if (IsValid(UAIBlueprintHelperLibrary::GetBlackboard(this)))
	{
		return UAIBlueprintHelperLibrary::GetBlackboard(this);
	}
	return nullptr;
}
