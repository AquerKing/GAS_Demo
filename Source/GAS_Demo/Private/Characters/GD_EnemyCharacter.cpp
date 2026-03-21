// Copyright AquerKing


#include "Characters/GD_EnemyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/GD_AbilitySystemComponent.h"


AGD_EnemyCharacter::AGD_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UGD_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

UAbilitySystemComponent* AGD_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AGD_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}

	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);

	if (!HasAuthority())
	{
		return;
	}

	GiveStartupAbilities();
}
