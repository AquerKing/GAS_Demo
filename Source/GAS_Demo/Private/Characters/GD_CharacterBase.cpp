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

UAttributeSet* AGD_CharacterBase::GetAttributeSet() const
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

void AGD_CharacterBase::InitializeAttributes() const
{
	checkf(IsValid(InitializedAttributesEffect), TEXT("InitializeAttributesEffect not set."));

	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(
		InitializedAttributesEffect, 1.0f, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
