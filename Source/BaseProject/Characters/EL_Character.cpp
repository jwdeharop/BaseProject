#include "EL_Character.h"
#include "EnhancedInputSubsystems.h"

AEL_Character::AEL_Character() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerEnhancedInputComponent = CreateDefaultSubobject<UEnhancedInputComponent>(TEXT("InputEnhancedComponent"));
}

void AEL_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AEL_Character::PawnClientRestart()
{
	Super::PawnClientRestart();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(BaseMappingContext, 0);
		}
	}
}

void AEL_Character::EnhancedInputMovement(const FInputActionValue& ActionValue)
{
	if (ActionValue.GetMagnitude() != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), ActionValue[1]);
		AddMovementInput(GetActorRightVector(), ActionValue[0]);
	}
}

void AEL_Character::EnhancedInputLook(const FInputActionValue& ActionValue)
{
	AddControllerPitchInput(ActionValue[1] * -1);
	AddControllerYawInput(ActionValue[0]);
}

void AEL_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEL_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerEnhancedInputComponent)
	{
		for (uint8 Index = 0U; Index < (uint8)EEL_ActionType::Num_Actions; ++Index)
		{
			EEL_ActionType ActionType = (EEL_ActionType)Index;
			if (FEL_CharacterActions* CharacterAction = EnhancedInputActions.Find(ActionType))
			{
				UInputAction* InputAction = CharacterAction->InputAction;
				switch (ActionType)
				{
					case EEL_ActionType::Movement:
					{
						PlayerEnhancedInputComponent->BindAction(InputAction,  CharacterAction->TriggerEvent, this, &AEL_Character::EnhancedInputMovement);
					}
					break;
				}
			}
		}
	}
}

