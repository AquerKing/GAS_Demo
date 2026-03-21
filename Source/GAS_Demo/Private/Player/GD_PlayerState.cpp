// Copyright AquerKing


#include "Player/GD_PlayerState.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GD_AbilitySystemComponent.h"

AGD_PlayerState::AGD_PlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UGD_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AGD_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
