// Copyright (C) 2024 owoDra

#include "InputProcessor_Ability.h"

#include "InputProcessComponent.h"

#include "GAEAbilitySystemComponent.h"

#include "AbilitySystemGlobals.h"
#include "GameFramework/Actor.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(InputProcessor_Ability)


UInputProcessor_Ability::UInputProcessor_Ability(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bBind_Triggered = false;
	bBind_Started = true;
	bBind_Ongoing = false;
	bBind_Canceled = false;
	bBind_Complete = true;
}


void UInputProcessor_Ability::OnInitialized_Implementation(UInputProcessComponent* InputComponent)
{
	StoreAbilitySystemComponent();
}

void UInputProcessor_Ability::OnDeinitialize_Implementation(UInputProcessComponent* InputComponent)
{
	AbilitySystemComponent.Reset();
}

void UInputProcessor_Ability::OnStarted_Implementation(const FGameplayTag& InputTag, const FInputActionValue& InputActionValue)
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->AbilityInputTagPressed(InputTag);
	}
}

void UInputProcessor_Ability::OnComplete_Implementation(const FGameplayTag& InputTag, const FInputActionValue& InputActionValue)
{
	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->AbilityInputTagReleased(InputTag);
	}
}

void UInputProcessor_Ability::StoreAbilitySystemComponent()
{
	if (auto* ASC{ UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetTypedOuter<AActor>()) })
	{
		AbilitySystemComponent = Cast<UGAEAbilitySystemComponent>(ASC);
	}
}
