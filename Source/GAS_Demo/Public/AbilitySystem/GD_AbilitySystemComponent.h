// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GD_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_DEMO_API UGD_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="GASDemo|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level);

	UFUNCTION(BlueprintCallable, Category="GASDemo|Abilities")
	void AddAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1);
	
protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

	virtual void OnRep_ActivateAbilities() override;

private:
	void HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec);
};
