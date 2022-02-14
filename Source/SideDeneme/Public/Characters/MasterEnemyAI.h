// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MasterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MasterEnemyAI.generated.h"

UCLASS()
class SIDEDENEME_API AMasterEnemyAI : public AMasterCharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Metin")
	virtual UBlackboardComponent* GetBlackboard();
};
