// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h" // Interface icin
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include <GameplayEffectTypes.h> 
#include "BaseCharacter.generated.h"

UCLASS()
class SIDEDENEME_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	class UGAS_AbilitySystemComponent* AbilitySystemComponent;

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FDelegateHandle DamageChangedDelegateHandle;
	FDelegateHandle MovementSpeedChangedDelegateHandle;
	FDelegateHandle FireRateChangedDelegateHandle;
	
	virtual void OnMovementSpeedChanged(const FOnAttributeChangeData& Data);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// GAS Part

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UFUNCTION(BlueprintCallable, Category = "CharacterBase") // Single Ability
	void AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase") // Multi Abilities
	void AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAquire);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
	class UBaseAttributeSet* MyAttributes;
	
	UFUNCTION(BlueprintImplementableEvent)
	void MovementSpeedChanged(float NewValue);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
		void ApplyGESpecHandleToTargetDataSpecsHandle(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	/** Blueprint-accessible getter for the current health value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetHealth() const;

	/** Blueprint-accessible getter for the max health value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetMaxHealth() const;

	/** Blueprint-accessible getter for the current mana value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetMana() const;

	/** Blueprint-accessible getter for the current damage value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetDamage() const;

	/** Blueprint-accessible getter for the current movement speed value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetMovementSpeed() const;

	/** Blueprint-accessible getter for the current fire rate value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetFireRate() const;

};
