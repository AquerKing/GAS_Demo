// Copyright AquerKing


#include "Player/GD_PlayerState.h"

#include "AbilitySystemComponent.h"

AGD_PlayerState::AGD_PlayerState()
{
	SetNetUpdateFrequency(100.0f);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

UAbilitySystemComponent* AGD_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
