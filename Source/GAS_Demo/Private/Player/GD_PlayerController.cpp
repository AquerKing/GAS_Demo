// Copyright AquerKing


#include "GAS_Demo/Public/Player/GD_PlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/Character.h"
#include "GameplayTags/GD_Tags.h"

void AGD_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem))
	{
		return;
	}

	for (UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
	                                   &AGD_PlayerController::Jump_ActionCallback);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
	                                   &AGD_PlayerController::StopJumping_ActionCallback);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
	                                   &AGD_PlayerController::Move_ActionCallback);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
	                                   &AGD_PlayerController::Look_ActionCallback);

	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this,
	                                   &AGD_PlayerController::Primary_ActionCallback);
	EnhancedInputComponent->BindAction(SecondaryAction, ETriggerEvent::Started, this,
	                                   &AGD_PlayerController::Secondary_ActionCallback);
	EnhancedInputComponent->BindAction(TertiaryAction, ETriggerEvent::Started, this,
	                                   &AGD_PlayerController::Tertiary_ActionCallback);
}

void AGD_PlayerController::Jump_ActionCallback()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}

	GetCharacter()->Jump();
}

void AGD_PlayerController::StopJumping_ActionCallback()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}

	GetCharacter()->StopJumping();
}

void AGD_PlayerController::Move_ActionCallback(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()))
	{
		return;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();

	// Find which way is forward
	const FRotator YawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

void AGD_PlayerController::Look_ActionCallback(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AGD_PlayerController::Primary_ActionCallback()
{
	ActivateAbility(GDTags::GDAbilities::Primary);
}

void AGD_PlayerController::Secondary_ActionCallback()
{
	ActivateAbility(GDTags::GDAbilities::Secondary);
}

void AGD_PlayerController::Tertiary_ActionCallback()
{
	ActivateAbility(GDTags::GDAbilities::Tertiary);
}

void AGD_PlayerController::ActivateAbility(const FGameplayTag& AbilityTag) const
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn());
	if (!IsValid(ASC))
	{
		return;
	}

	ASC->TryActivateAbilitiesByTag(AbilityTag.GetSingleTagContainer());
}
