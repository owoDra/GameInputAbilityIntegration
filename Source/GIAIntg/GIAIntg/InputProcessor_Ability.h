// Copyright (C) 2024 owoDra

#pragma once

#include "Processor/InputProcessor.h"

#include "InputProcessor_Ability.generated.h"

class UGAEAbilitySystemComponent;


/**
 * Class for performing specific input processing of actors
 */
UCLASS()
class GIAINTG_API UInputProcessor_Ability : public UInputProcessor
{
	GENERATED_BODY()
public:
	UInputProcessor_Ability(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(Transient)
	TWeakObjectPtr<UGAEAbilitySystemComponent> AbilitySystemComponent;

public:
	virtual void OnInitialized_Implementation(UInputProcessComponent* InputComponent) override;
	virtual void OnDeinitialize_Implementation(UInputProcessComponent* InputComponent) override;

protected:
	virtual void OnStarted_Implementation(const FGameplayTag& InputTag, const FInputActionValue& InputActionValue) override;
	virtual void OnComplete_Implementation(const FGameplayTag& InputTag, const FInputActionValue& InputActionValue) override;

	void StoreAbilitySystemComponent();
};
