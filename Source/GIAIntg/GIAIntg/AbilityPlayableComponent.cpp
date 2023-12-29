// Copyright (C) 2023 owoDra

#include "AbilityPlayableComponent.h"

#include "GIAIntgLogs.h"

#include "GAEAbilitySystemComponent.h"

#include "Actor/GFCPlayerController.h"
#include "InitState/InitStateTags.h"

#include "AbilitySystemGlobals.h"
#include "GameFramework/Pawn.h"
#include "Components/GameFrameworkComponentManager.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AbilityPlayableComponent)


UAbilityPlayableComponent::UAbilityPlayableComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


void UAbilityPlayableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UninitializeFromAbilitySystem();

	Super::EndPlay(EndPlayReason);
}


void UAbilityPlayableComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	Super::OnActorInitStateChanged(Params);

	// Wait for initialization of AbilitySystemCompoenet

	if (Params.FeatureName == UGAEAbilitySystemComponent::NAME_ActorFeatureName)
	{
		if (Params.FeatureState == TAG_InitState_DataInitialized)
		{
			CheckDefaultInitialization();
		}
	}
}


bool UAbilityPlayableComponent::CanChangeInitStateToDataInitialized(UGameFrameworkComponentManager* Manager) const
{
	if (!DefaultInputConfig)
	{
		return false;
	}

	if (!Manager->HasFeatureReachedInitState(GetOwner(), UGAEAbilitySystemComponent::NAME_ActorFeatureName, TAG_InitState_DataInitialized))
	{
		return false;
	}

	return true;
}

void UAbilityPlayableComponent::HandleChangeInitStateToDataInitialized(UGameFrameworkComponentManager* Manager)
{
	InitializeWithAbilitySystem();

	if (auto* Pawn{ GetPawnChecked<APawn>() })
	{
		InitializePlayerInput(Pawn->GetController());
	}
}


void UAbilityPlayableComponent::InitializePlayerInput(AController* Controller)
{
	if (auto* PC{ Cast<AGFCPlayerController>(Controller) })
	{
		PC->OnPostProcessInput.AddUObject(this, &ThisClass::ProcessAbilityInput);
	}

	Super::InitializePlayerInput(Controller);
}

void UAbilityPlayableComponent::UninitializePlayerInput(AController* Controller)
{
	if (auto* PC{ Cast<AGFCPlayerController>(Controller) })
	{
		PC->OnPostProcessInput.RemoveAll(this);
	}

	Super::UninitializePlayerInput(Controller);
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
}

void UAbilityPlayableComponent::UninitializeFromAbilitySystem()
{
	AbilitySystemComponent = nullptr;
}


void UAbilityPlayableComponent::ProcessAbilityInput(const float DeltaTime, const bool bGamePaused)
{
	if (auto* GAEASC{ Cast<UGAEAbilitySystemComponent>(AbilitySystemComponent) })
	{
		GAEASC->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
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
