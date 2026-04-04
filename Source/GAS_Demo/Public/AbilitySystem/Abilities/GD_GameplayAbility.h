// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GD_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_DEMO_API UGD_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASDemo|Debug")
	bool bDrawDebugs = false;
};
