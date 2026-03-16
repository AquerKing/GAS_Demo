// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "GD_CharacterBase.h"
#include "GD_PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class GAS_DEMO_API AGD_PlayerCharacter : public AGD_CharacterBase
{
	GENERATED_BODY()

public:
	AGD_PlayerCharacter();

private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
};
