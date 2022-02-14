// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/BaseCharacter.h"
#include "GAS_AbilitySystemComponent.h"
#include "GAS/BaseAttributeSet.h"
#include "GAS/GameplayAbilityBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGAS_AbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	MyAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeComp"));

	MovementSpeedChangedDelegateHandle = AbilitySystemComponent->
								  GetGameplayAttributeValueChangeDelegate(MyAttributes->GetMovementSpeedAttribute()).
								  AddUObject(this, &ABaseCharacter::OnMovementSpeedChanged);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	/*Attributes->OnHealthChange.AddDynamic(this, &ABaseCharacter::OnHealthChanged);
	Attributes->OnManaChange.AddDynamic(this, &ABaseCharacter::OnManaChanged);*/

}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseCharacter::OnMovementSpeedChanged(const FOnAttributeChangeData& Data)
{
	MovementSpeedChanged(Data.NewValue);
}

// Getters for Blueprint
float ABaseCharacter::GetHealth() const
{
	if(IsValid(MyAttributes))
	{
		return MyAttributes->GetHealth();
	}

	return -1.0f;
}

float ABaseCharacter::GetMaxHealth() const
{
	if(IsValid(MyAttributes))
	{
		return MyAttributes->GetMaxHealth();
	}
	
	return -1.0f;
}

float ABaseCharacter::GetMana() const
{
	if(IsValid(MyAttributes))
	{
		return MyAttributes->GetMana();
	}
	
	return -1.0f;
}

float ABaseCharacter::GetDamage() const
{
	if(IsValid(MyAttributes))
	{
		return MyAttributes->GetDamage();
	}
	
	return -1.0f;
}

float ABaseCharacter::GetMovementSpeed() const
{
	if(IsValid(MyAttributes))
	{
		return MyAttributes->GetMovementSpeed();
	}
	
	return -1.0f;
}

float ABaseCharacter::GetFireRate() const
{
	if(IsValid(MyAttributes))
	{
		return MyAttributes->GetFireRate();
	}
	
	return -1.0f;
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Gives an Ability to related character
void ABaseCharacter::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (AbilitySystemComponent)
	{
		if (HasAuthority() && AbilityToAquire)
		{
			AbilitySystemComponent->GiveAbility(
				FGameplayAbilitySpec(AbilityToAquire, 1, 0));
		}
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

// Called from BP and gives all abilities 
void ABaseCharacter::AquireAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToAquire)
{
	if (AbilitySystemComponent)
	{
		for (TSubclassOf<UGameplayAbility> AbilityItem : AbilitiesToAquire)
		{
			AquireAbility(AbilityItem);
			if (AbilityItem->IsChildOf(UGameplayAbilityBase::StaticClass()))
			{
				TSubclassOf<UGameplayAbilityBase> AbilityBaseClass = *AbilityItem;
			}
		}
	}
}



void ABaseCharacter::ApplyGESpecHandleToTargetDataSpecsHandle(const FGameplayEffectSpecHandle& GESpecHandle,
	const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	for (TSharedPtr<FGameplayAbilityTargetData> Data : TargetDataHandle.Data)
	{
		Data->ApplyGameplayEffectSpec(*GESpecHandle.Data.Get());
	}

}

