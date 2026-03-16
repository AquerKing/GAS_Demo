// Copyright AquerKing


#include "GAS_Demo/Public/Characters/GD_CharacterBase.h"


AGD_CharacterBase::AGD_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Tick and refresh bone transforms whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption =
		EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}
