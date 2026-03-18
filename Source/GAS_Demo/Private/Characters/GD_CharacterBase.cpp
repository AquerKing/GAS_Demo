// Copyright AquerKing


#include "GAS_Demo/Public/Characters/GD_CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"


AGD_CharacterBase::AGD_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

UAbilitySystemComponent* AGD_CharacterBase::GetAbilitySystemComponent() const
{
	return nullptr;
}

void AGD_CharacterBase::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}
	
	for (const auto& Ability : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}
