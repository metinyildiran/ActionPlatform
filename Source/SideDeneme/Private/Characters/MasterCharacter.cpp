// Fill out your copyright notice in the Description page of Project Settings.

#include "SideDeneme/Public/Characters/MasterCharacter.h"
#include "SideDeneme/Public/GAS_AbilitySystemComponent.h"
#include "SideDeneme/Public/Characters/Abilities/AttributeSets/GAS_AttributeSetBase.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UI/HeadsUpDisplayWidget.h"
#include "UI/PlayerUIWidget.h"

AMasterCharacter::AMasterCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UGAS_AttributeSetBase>(TEXT("GAS_AttributeSetBase"));

	// UHeadsUpDisplayWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(FName("HeadsUpDisplayWidget"));
	// UHeadsUpDisplayWidgetComponent->SetupAttachment(RootComponent);
	// UHeadsUpDisplayWidgetComponent->SetRelativeLocation(FVector(0, 0, 120));
	// UHeadsUpDisplayWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	// UHeadsUpDisplayWidgetComponent->SetDrawSize(FVector2D(500, 500));

	// UHeadsUpDisplayWidgetClass = StaticLoadClass(UObject::StaticClass(), nullptr,
	//                                              TEXT(
	// 	                                             "/Game/Characters/Widget_HeadsUpDisplay.Widget_HeadsUpDisplay_C"));
	// if (!UHeadsUpDisplayWidgetClass)
	// {
	// 	UE_LOG(LogTemp, Error,
	// 	       TEXT(
	// 		       "%s() Failed to find UIFloatingStatusBarClass. If it was moved, please update the reference location in C++."
	// 	       ), *FString(__FUNCTION__));
	// }

	// Attribute changed delegates
	HealthChangedDelegateHandle = AbilitySystemComponent->
	                              GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).
	                              AddUObject(this, &AMasterCharacter::OnHealthChanged);
	MaxHealthChangedDelegateHandle = AbilitySystemComponent->
	                                 GetGameplayAttributeValueChangeDelegate(AttributeSet->GetMaxHealthAttribute()).
	                                 AddUObject(this, &AMasterCharacter::OnMaxHealthChanged);
	DamageChangedDelegateHandle = AbilitySystemComponent->
	                              GetGameplayAttributeValueChangeDelegate(AttributeSet->GetDamageAttribute()).
	                              AddUObject(this, &AMasterCharacter::OnDamageChanged);
	MovementSpeedChangedDelegateHandle = AbilitySystemComponent->
	                                     GetGameplayAttributeValueChangeDelegate(
		                                     AttributeSet->GetMovementSpeedAttribute()).
	                                     AddUObject(this, &AMasterCharacter::OnMovementSpeedChanged);
	FireRateChangedDelegateHandle = AbilitySystemComponent->
	                                GetGameplayAttributeValueChangeDelegate(AttributeSet->GetFireRateAttribute()).
	                                AddUObject(this, &AMasterCharacter::OnFireRateChanged);
}

void AMasterCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Initializes the attribute set using a data table.
	// if (IsValid(AbilitySystemComponent))
	// {
	// 	AttributeSet = AbilitySystemComponent->GetSet<UGAS_AttributeSetBase>();
	//
	// 	// //GetGameplayAttributeValueChangedDelegate will enable you to bind delegates without programming them manually.
	// 	// AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(
	// 	// 	this, &AMasterCharacter::OnHealthChangedInternal);
	// }

	if (AttributeSet)
	{
		AttributeSet->InitHealth(100.0f);
		AttributeSet->InitMaxHealth(100.0f);
		AttributeSet->InitDamage(1.0f);
		AttributeSet->InitMovementSpeed(600.0f);
		AttributeSet->InitFireRate(1.0f);
		AttributeSet->InitSkillCooldown(1.0f);
	}
	
	// APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// if (!HasAuthority() && UHeadsUpDisplayWidgetClass && PC->IsLocalPlayerController())
	// {
	// 	UHeadsUpDisplay = CreateWidget<UHeadsUpDisplayWidget>(PC, UHeadsUpDisplayWidgetClass);
	// 	if (UHeadsUpDisplay && UHeadsUpDisplayWidgetComponent)
	// 	{
	// 		UHeadsUpDisplayWidgetComponent->SetWidget(UHeadsUpDisplay);
	// 	
	// 		// Setup the floating status bar
	// 		UHeadsUpDisplay->SetHealthPercentage(GetHealth() / GetMaxHealth());
	// 	}
	// }
}

UAbilitySystemComponent* AMasterCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Attribute changed callbacks
void AMasterCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	// // If the minion died, handle death
	// if (!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	// {
	// 	Die();
	// }

	// Call EventSetHealthPercentage on HeadsUpDisplay
	// if (UHeadsUpDisplay)
	// {
	// 	UHeadsUpDisplay->SetHealthPercentage(Health / GetMaxHealth());
	// }

	// Call EventSetHealthPercentage on UI
	if (Widget)
	{
		Widget->SetHealthPercentage(Health / GetMaxHealth());
	}

	// Die
	if (Health == 0.0)
	{
		Destroy();
	}
}

void AMasterCharacter::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
}

void AMasterCharacter::OnDamageChanged(const FOnAttributeChangeData& Data)
{
}

void AMasterCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	// GetCharacterMovement()->MaxWalkSpeed = GetMovementSpeed();
	MovementSpeedChanged(Data.NewValue);
}

void AMasterCharacter::OnFireRateChanged(const FOnAttributeChangeData& Data)
{
}

//Getters for attributes. All of these have bail-out logic for if the AttributeSet isn't initialized correctly.
float AMasterCharacter::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}

	return -1.0f;
}

float AMasterCharacter::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxHealth();
	}

	return -1.0f;
}

float AMasterCharacter::GetDamage() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetDamage();
	}

	return -1.0f;
}

float AMasterCharacter::GetMovementSpeed() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMovementSpeed();
	}

	return -1.0f;
}

float AMasterCharacter::GetFireRate() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetFireRate();
	}

	return -1.0f;
}

void AMasterCharacter::CancelAbilityWithTags(const FGameplayTagContainer CancelWithTags)
{
	//The Ability System Component has multiple ways of cancelling and activating abilities. Using tags provides a generic means of categorizing different types of abilities without knowing what specific ability is active.
	AbilitySystemComponent->CancelAbilities(&CancelWithTags);
}

//Create an instance of an Ability and add it to the Ability System Component.
void AMasterCharacter::GrantAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level, int32 InputCode)
{
	if (GetLocalRole() == ROLE_Authority && IsValid(AbilitySystemComponent) && IsValid(AbilityClass))
	{
		UGameplayAbility* Ability = AbilityClass->GetDefaultObject<UGameplayAbility>();

		if (IsValid(Ability))
		{
			// create the new ability spec struct. Ability specs contain metadata about the ability, like what level they're set to, as well as a reference to the ability.
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, Level, InputCode));
		}
	}
}

void AMasterCharacter::ActivateAbility(int32 InputCode)
{
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->AbilityLocalInputPressed(InputCode);
	}
}

// Server GAS init
// void AMasterCharacter::PossessedBy(AController* NewController)
// {
// 	Super::PossessedBy(NewController);
//
// 	AGAS_PlayerState* PS = GetPlayerState<AGAS_PlayerState>();
// 	if (PS)
// 	{
// 		// Set the ASC on the Server. Clients do this in OnRep_PlayerState()
// 		AbilitySystemComponent = Cast<UGAS_AbilitySystemComponent>(PS->GetAbilitySystemComponent());
// 		
// 		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
//
// 		// Set the AttributeSetBase for convenience attribute functions
// 		AttributeSet = PS->GetAttributeSetBase();
// 	}
// }

// Server GAS init
void AMasterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	// ASC MixedMode replication requires that the ASC Owner's Owner be the Controller.
	SetOwner(NewController);
}

// Client GAS init
// void AMasterCharacter::OnRep_PlayerState()
// {
// 	Super::OnRep_PlayerState();
//
// 	AGAS_PlayerState* PS = GetPlayerState<AGAS_PlayerState>();
// 	if (PS)
// 	{
// 		// Set the ASC for clients. Server does this in PossessedBy()
// 		AbilitySystemComponent = Cast<UGAS_AbilitySystemComponent>(PS->GetAbilitySystemComponent());
//
// 		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
//
// 		AttributeSet = PS->GetAttributeSetBase();
// 	}
// }

// Client GAS init
void AMasterCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
