// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GD_AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "GD_AttributeWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAS_DEMO_API UGD_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GASDemo|Attributes")
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GASDemo|Attributes")
	FGameplayAttribute MaxAttribute;

	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UGD_AttributeSet* AttributeSet);
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION(BlueprintImplementableEvent, meta=(DiplayName="On Attribute Change"))
	void BP_OnAttributeChange(float NewValue, float NewMaxValue);
};
