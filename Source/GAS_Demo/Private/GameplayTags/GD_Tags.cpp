#include "GameplayTags/GD_Tags.h"

namespace GDTags
{
	namespace GDAbilities
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GDTags.GDAbilities.ActivateOnGiven",
		                               "Tag for Abilities that should activate immediately once given.")

		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GDTags.GDAbilities.Primary", "Tag for the Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GDTags.GDAbilities.Secondary",
		                               "Tag for the Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GDTags.GDAbilities.Tertiary",
		                               "Tag for the Tertiary Ability")
	}

	namespace Events
	{
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GDTags.Events.Enemy.HitReact",
			                               "Tag for the Enemy HitReact Event")
		}
	}
}
