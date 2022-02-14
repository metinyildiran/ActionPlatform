// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, Health, float, MaxHealth);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedDelegate, float, Mana, float, MaxMana);

UCLASS()
class SIDEDENEME_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UBaseAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	// Health Variables
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxHealth);

	// FOnHealthChangedDelegate OnHealthChange;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Damage);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MovementSpeed);

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData FireRate;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, FireRate);
	
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData SkillCooldown;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, SkillCooldown);

	// Mana Variables
	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSet")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, MaxMana);

	// FOnManaChangedDelegate OnManaChange;

	
	// Modify attributes
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

};
