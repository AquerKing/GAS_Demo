// Copyright AquerKing


#include "Characters/GD_EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GD_AbilitySystemComponent.h"
#include "AbilitySystem/GD_AttributeSet.h"


AGD_EnemyCharacter::AGD_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UGD_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UGD_AttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGD_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AGD_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
}

void AGD_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());

	if (!HasAuthority())
	{
		return;
	}

	GiveStartupAbilities();
	InitializeAttributes();
}
