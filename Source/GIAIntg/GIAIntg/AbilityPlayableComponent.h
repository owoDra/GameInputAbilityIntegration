// Copyright (C) 2023 owoDra

#pragma once

#include "PlayableComponent.h"

#include "AbilityPlayableComponent.generated.h"

class UAbilitySystemComponent;


/**
 * Component that initializes the player-controlled Pawn Input
 */
UCLASS(Meta = (BlueprintSpawnableComponent))
class GIAINTG_API UAbilityPlayableComponent : public UPlayableComponent
{
	GENERATED_BODY()
public:
	UAbilityPlayableComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;


protected:
	UPROPERTY(Transient)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent{ nullptr };

protected:
	void InitializeWithAbilitySystem();
	void UninitializeFromAbilitySystem();


protected:
	virtual void TagInput_PressedExtra(FGameplayTag InputTag) override;
	virtual void TagInput_ReleasedExtra(FGameplayTag InputTag) override;

};
