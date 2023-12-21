// Copyright (C) 2023 owoDra

#include "AbilityPlayableComponent.h"

#include "GIAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"

#include "InitState/InitStateTags.h"

#include "AbilitySystemGlobals.h"
#include "GameFramework/Pawn.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityPlayableComponent)


UAbilityPlayableComponent::UAbilityPlayableComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


bool UAbilityPlayableComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	auto* Pawn{ GetPawn<APawn>() };

	/**
	 * [InitState None] -> [InitState Spawned]
	 */
	if (!CurrentState.IsValid() && DesiredState == TAG_InitState_Spawned)
	{
		if (Pawn)
		{
			return true;
		}
	}

	/**
	 * [InitState Spawned] -> [InitState DataAvailable]
	 */
	else if (CurrentState == TAG_InitState_Spawned && DesiredState == TAG_InitState_DataAvailable)
	{
		// Check if it is not SimulationProxy

		if (Pawn->GetLocalRole() == ROLE_SimulatedProxy)
		{
			return false;
		}

		// Check if it is not a bot player

		const auto bIsLocallyControlled{ Pawn->IsLocallyControlled() };
		const auto bIsBot{ Pawn->IsBotControlled() };

		if (!bIsLocallyControlled || bIsBot)
		{
			return false;
		}

		// Check has valid input component

		if (!Pawn->InputComponent)
		{
			return false;
		}

		return Manager->HasFeatureReachedInitState(Pawn, UGAEAbilitySystemComponent::NAME_ActorFeatureName, TAG_InitState_DataInitialized);
	}

	/**
	 * [InitState DataAvailable] -> [InitState DataInitialized]
	 */
	else if (CurrentState == TAG_InitState_DataAvailable && DesiredState == TAG_InitState_DataInitialized)
	{
		if (AbilitySystemComponent && DefaultInputConfig)
		{
			return true;
		}
	}

	/**
	 * [InitState DataInitialized] -> [InitState GameplayReady]
	 */
	else if (CurrentState == TAG_InitState_DataInitialized && DesiredState == TAG_InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void UAbilityPlayableComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	UE_LOG(LogGIAI, Log, TEXT("[%s] Ability Playable Component InitState Reached: %s"),
		GetOwner()->HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *DesiredState.GetTagName().ToString());

	/**
	 * [InitState Spawned] -> [InitState DataAvailable]
	 */
	if (CurrentState == TAG_InitState_Spawned && DesiredState == TAG_InitState_DataAvailable)
	{
		InitializeWithAbilitySystem();
	}

	/**
	 * [InitState DataAvailable] -> [InitState DataInitialized]
	 */
	else if (CurrentState == TAG_InitState_DataAvailable && DesiredState == TAG_InitState_DataInitialized)
	{
		InitializePlayerInput();
	}
}

void UAbilityPlayableComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	// Wait for initialization of AbilitySystemCompoenet

	if (Params.FeatureName == UGAEAbilitySystemComponent::NAME_ActorFeatureName)
	{
		if ((Params.FeatureState == TAG_InitState_DataInitialized) || (Params.FeatureState == TAG_InitState_GameplayReady))
		{
			CheckDefaultInitialization();
		}
	}
}


void UAbilityPlayableComponent::InitializeWithAbilitySystem()
{
	auto* Pawn{ GetPawn<APawn>() };
	check(Pawn);

	auto* NewASC{ UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Pawn) };

	if (AbilitySystemComponent)
	{
		if (AbilitySystemComponent == NewASC)
		{
			return;
		}

		UninitializeFromAbilitySystem();
	}

	AbilitySystemComponent = NewASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogGIAI, Error, TEXT("Ability Playable Component: Cannot initialize Ability Playable component for owner [%s] with NULL ability system."), *GetNameSafe(Pawn));
		return;
	}

	CheckDefaultInitialization();
}

void UAbilityPlayableComponent::UninitializeFromAbilitySystem()
{
	AbilitySystemComponent = nullptr;
}


void UAbilityPlayableComponent::TagInput_PressedExtra(FGameplayTag InputTag)
{
	if (auto* GAEASC{ Cast<UGAEAbilitySystemComponent>(AbilitySystemComponent) })
	{
		GAEASC->AbilityInputTagPressed(InputTag);
	}
}

void UAbilityPlayableComponent::TagInput_ReleasedExtra(FGameplayTag InputTag)
{
	if (auto* GAEASC{ Cast<UGAEAbilitySystemComponent>(AbilitySystemComponent) })
	{
		GAEASC->AbilityInputTagReleased(InputTag);
	}
}
