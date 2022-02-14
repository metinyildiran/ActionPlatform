// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BulletMaster.h"
#include "SideDeneme/Public/GAS_AbilitySystemComponent.h"

// Sets default values
ABulletMaster::ABulletMaster()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

}

class UAbilitySystemComponent* ABulletMaster::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
