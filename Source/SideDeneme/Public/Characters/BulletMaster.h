// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "BulletMaster.generated.h"

UCLASS()
class SIDEDENEME_API ABulletMaster : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	class UGAS_AbilitySystemComponent* AbilitySystemComponent;
	
public:	
	// Sets default values for this actor's properties
	ABulletMaster();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
