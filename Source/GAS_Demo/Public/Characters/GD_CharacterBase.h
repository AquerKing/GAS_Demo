// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GD_CharacterBase.generated.h"

class UGameplayAbility;

UCLASS(Abstract)
class GAS_DEMO_API AGD_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGD_CharacterBase();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	void GiveStartupAbilities();
	
private:
	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
