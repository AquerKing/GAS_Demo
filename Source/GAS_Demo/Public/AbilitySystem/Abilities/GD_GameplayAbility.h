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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="GASDemo|Debug")
	bool bDrawDebugs = false;
};
