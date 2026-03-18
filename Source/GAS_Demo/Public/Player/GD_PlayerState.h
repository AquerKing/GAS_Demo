// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GD_PlayerState.generated.h"

class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class GAS_DEMO_API AGD_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGD_PlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY(VisibleAnywhere, Category="GASDemo|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
};
