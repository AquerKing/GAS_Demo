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

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input|Movement")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input|Movement")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input|Movement")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category="GASDemo|Input|Abilities")
	TObjectPtr<UInputAction> PrimaryAction;

	void Jump_ActionCallback();
	void StopJumping_ActionCallback();
	void Move_ActionCallback(const FInputActionValue& Value);
	void Look_ActionCallback(const FInputActionValue& Value);
	
	void Primary_ActionCallback();
};
