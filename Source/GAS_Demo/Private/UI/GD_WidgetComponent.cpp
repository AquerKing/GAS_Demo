// Copyright AquerKing


#include "UI/GD_WidgetComponent.h"

#include "AbilitySystem/GD_AbilitySystemComponent.h"
#include "AbilitySystem/GD_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/GD_CharacterBase.h"
#include "UI/GD_AttributeWidget.h"


void UGD_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystemData();

	if (!IsASCInitialized())
	{
		TargetCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
	}
	else
	{
		InitializeAttributeDelegate();
	}
}

void UGD_WidgetComponent::InitAbilitySystemData()
{
	TargetCharacter = Cast<AGD_CharacterBase>(GetOwner());
	AttributeSet = Cast<UGD_AttributeSet>(TargetCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UGD_AbilitySystemComponent>(TargetCharacter->GetAbilitySystemComponent());
}

bool UGD_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UGD_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

void UGD_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject,
                                                       const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UGD_AttributeWidget* AttributeWidget = Cast<UGD_AttributeWidget>(WidgetObject);

	if (!IsValid(AttributeWidget)) return; // only care about GD Attribute Widgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // only subscribe for matching attributes

	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for initial values

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda(
		[this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData) {
			AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // for changes during the game
		});
}

void UGD_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGD_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGD_AttributeSet>(AS);

	if (!IsASCInitialized()) return;

	InitializeAttributeDelegate();
}

void UGD_WidgetComponent::BindToAttributeChanges()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair); // for checking the owned widget object

		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget) {
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}
