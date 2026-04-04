// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "GD_CharacterBase.h"
#include "GD_EnemyCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class GAS_DEMO_API AGD_EnemyCharacter : public AGD_CharacterBase
{
	GENERATED_BODY()

public:
	AGD_EnemyCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
