// Fill out your copyright notice in the Description page of Project Settings.

#include "SideDeneme/Public/Characters/Abilities/AttributeSets/GAS_AttributeSetBase.h"
#include "AttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

//The PostGameplayEffectExecute function handles any logic that should happen after a GameplayEffect is applied to the Ability System Component that owns this AttributeSet. In effect it "listens" for changes to happen.
void UGAS_AttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	//Clamping Health based on Max Health.
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void UGAS_AttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSetBase, Damage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSetBase, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSetBase, FireRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGAS_AttributeSetBase, SkillCooldown, COND_None, REPNOTIFY_Always);
}

void UGAS_AttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSetBase, Health, OldHealth);
}

void UGAS_AttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSetBase, MaxHealth, OldMaxHealth);
}

void UGAS_AttributeSetBase::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSetBase, Damage, OldDamage);
}

void UGAS_AttributeSetBase::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSetBase, MovementSpeed, OldMovementSpeed);
}

void UGAS_AttributeSetBase::OnRep_FireRate(const FGameplayAttributeData& OldFireRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSetBase, FireRate, OldFireRate);
}

void UGAS_AttributeSetBase::OnRep_SkillCooldown(const FGameplayAttributeData& OldSkillCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGAS_AttributeSetBase, SkillCooldown, OldSkillCooldown);
}
