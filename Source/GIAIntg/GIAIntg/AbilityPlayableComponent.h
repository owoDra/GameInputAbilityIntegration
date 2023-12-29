// Copyright (C) 2023 owoDra

#pragma once

#include "PlayableComponent.h"

#include "AbilityPlayableComponent.generated.h"

class UAbilitySystemComponent;
class AGFCPlayerController;


/**
 * Component that initializes the player-controlled Pawn Input
 */
UCLASS(Meta = (BlueprintSpawnableComponent))
class GIAINTG_API UAbilityPlayableComponent : public UPlayableComponent
{
	GENERATED_BODY()
public:
	UAbilityPlayableComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;

protected:
	virtual bool CanChangeInitStateToDataInitialized(UGameFrameworkComponentManager* Manager) const override;
	virtual void HandleChangeInitStateToDataInitialized(UGameFrameworkComponentManager* Manager) override;


protected:
	UPROPERTY(Transient)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };

	FDelegateHandle ProcessAbilityInputHandle;

protected:
	virtual void InitializePlayerInput(AController* Controller) override;
	virtual void UninitializePlayerInput(AController* Controller) override;

	void InitializeWithAbilitySystem();
	void UninitializeFromAbilitySystem();


protected:
	void ProcessAbilityInput(const float DeltaTime, const bool bGamePaused);

	virtual void TagInput_PressedExtra(FGameplayTag InputTag) override;
	virtual void TagInput_ReleasedExtra(FGameplayTag InputTag) override;

};
