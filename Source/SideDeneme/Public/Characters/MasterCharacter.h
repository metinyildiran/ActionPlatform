// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GameplayTagContainer.h"
#include "GameplayEffectTypes.h"
#include "MasterCharacter.generated.h"

//Implements IAbilitySystemInterface so that the ability system component can be accessed without needing to know the specific class.
UCLASS()
class SIDEDENEME_API AMasterCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacter();

	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UHeadsUpDisplayWidget> UHeadsUpDisplayWidgetClass;

	UPROPERTY()
	UHeadsUpDisplayWidget* UHeadsUpDisplay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	TSubclassOf<class UPlayerUIWidget> UPlayerUIWidgetClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UPlayerUIWidget* Widget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "UI")
	class UWidgetComponent* UHeadsUpDisplayWidgetComponent;

	/** Blueprint-accessible getter for the current health value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetHealth() const;

	/** Blueprint-accessible getter for the max health value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetMaxHealth() const;

	/** Blueprint-accessible getter for the current damage value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetDamage() const;

	/** Blueprint-accessible getter for the current movement speed value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetMovementSpeed() const;

	/** Blueprint-accessible getter for the current fire rate value. */
	UFUNCTION(BlueprintPure, Category = "Abilities|Attributes")
	float GetFireRate() const;

	/** Grants an ability at the given level, with an input code used to pick and choose which ability should be triggered. */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode);

	/** Activates an ability with a matching input code */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void ActivateAbility(int32 InputCode);

	/** Cancels abilities with specific Gameplay Tags applied to them.*/
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CancelAbilityWithTags(const FGameplayTagContainer CancelWithTags);

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = GAS, meta = (AllowPrivateAccess = "true"))
	class UGAS_AbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	class UGAS_AttributeSetBase* AttributeSet;

	//Function to bind to Attribute Changed delegate.
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle DamageChangedDelegateHandle;
	FDelegateHandle MovementSpeedChangedDelegateHandle;
	FDelegateHandle FireRateChangedDelegateHandle;

	// Attribute changed callbacks
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnDamageChanged(const FOnAttributeChangeData& Data);
	virtual void OnMovementSpeedChanged(const FOnAttributeChangeData& Data);
	virtual void OnFireRateChanged(const FOnAttributeChangeData& Data);
	
	UFUNCTION(BlueprintImplementableEvent)
	void MovementSpeedChanged(float NewValue);
};
