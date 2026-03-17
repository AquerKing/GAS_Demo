// Copyright AquerKing

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GD_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GAS_DEMO_API AGD_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input")
	TObjectPtr<UInputAction> LookAction;

	void Jump();
	void StopJumping();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
