// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GD_CharacterBase.generated.h"

class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class GAS_DEMO_API AGD_CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGD_CharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const;
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;

protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;

private:
	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Effects")
	TSubclassOf<UGameplayEffect> InitializedAttributesEffect;
};
