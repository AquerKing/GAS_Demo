// Copyright AquerKing


#include "AbilitySystem/Abilities/Player/GD_Primary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameplayTags/GD_Tags.h"

TArray<AActor*> UGD_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	// Ensure that the overlap test ignores the avatar actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);

	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);

	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardRadius;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(
		0.0f, 0.0f, HitBoxElevationRadius);

	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Visibility,
	                                  Sphere, QueryParams, ResponseParams);

	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) continue;
		ActorsHit.AddUnique(Result.GetActor());
	}

	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(OverlapResults, HitBoxLocation);
	}

	return ActorsHit;
}

void UGD_Primary::SendHitReactEventToActor(const TArray<AActor*>& ActorsHit)
{
	for (AActor* HitActor : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, GDTags::Events::Enemy::HitReact,
		                                                         Payload);
	}
}

void UGD_Primary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults,
                                          const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.0f);
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) continue;

		FVector DebugLocation = Result.GetActor()->GetActorLocation();
		DebugLocation.Z += 100.0f;
		DrawDebugSphere(GetWorld(), DebugLocation, 30.0f, 10, FColor::Green, false, 3.0f);
	}
}
