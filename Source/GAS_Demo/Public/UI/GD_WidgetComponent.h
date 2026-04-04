// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/WidgetComponent.h"
#include "GD_WidgetComponent.generated.h"


class UAttributeSet;
class UGD_AttributeSet;
class UGD_AbilitySystemComponent;
class AGD_CharacterBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_DEMO_API UGD_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;

private:
	TWeakObjectPtr<AGD_CharacterBase> TargetCharacter;
	TWeakObjectPtr<UGD_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UGD_AttributeSet> AttributeSet;

	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void InitializeAttributeDelegate();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION()
	void BindToAttributeChanges();
};
