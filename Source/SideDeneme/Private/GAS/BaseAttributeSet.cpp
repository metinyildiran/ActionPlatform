// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	Health = 100.f; // Replicated
	MaxHealth = 100.f; // Not Replicated due to no necessary to be replicated.

	Mana = 100.f; // Replicated
	MaxMana = 100.f; // Not Replicated due to no necessary to be replicated.

	Damage = 10.0f;
	MovementSpeed = 600.0f;
	FireRate = 1.0f;
	SkillCooldown = 1.0f;
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME(UBaseAttributeSet, Health);
	DOREPLIFETIME(UBaseAttributeSet, Mana);
	DOREPLIFETIME(UBaseAttributeSet, Damage);
	DOREPLIFETIME(UBaseAttributeSet, MovementSpeed);
	DOREPLIFETIME(UBaseAttributeSet, FireRate);
	DOREPLIFETIME(UBaseAttributeSet, SkillCooldown);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	// When an effect executed, this function checks which value is evaluated. According to "EvaluatedData", it sets Data. There are health and mana at the moment.
	// If in the future some attributes would be want to added just copy the expression that in one of the if keyword. Also don't forget to make it replicated.
	
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.f, MaxHealth.GetCurrentValue()));

		UE_LOG(LogTemp, Warning, TEXT("Health is: %f"), Health.GetCurrentValue());
		// OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
	
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<FProperty>(UBaseAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UBaseAttributeSet, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.f, MaxMana.GetCurrentValue()));

		UE_LOG(LogTemp, Warning, TEXT("Mana %f"), Mana.GetCurrentValue());
		// OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}
}
