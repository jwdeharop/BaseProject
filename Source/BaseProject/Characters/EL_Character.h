// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "EL_Character.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UEnhancedInputComponent;
class UInputAction;
class UInputMappingContext;

UENUM(BlueprintType)
enum class EEL_ActionType : uint8
{
	None,
	Movement,
	Looking,

	Num_Actions
};

USTRUCT(BlueprintType)
struct FEL_CharacterActions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
		UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly)
		ETriggerEvent TriggerEvent;
};

UCLASS()
class BASEPROJECT_API AEL_Character : public ACharacter
{
	GENERATED_BODY()

public:

	AEL_Character();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

protected:

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(VisibleDefaultsOnly, Category = Input)
		UEnhancedInputComponent* PlayerEnhancedInputComponent;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		UInputMappingContext* BaseMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = Input)
		TMap<EEL_ActionType, FEL_CharacterActions> EnhancedInputActions;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float TurnRateGamepad;

	virtual void BeginPlay() override;
	virtual void PawnClientRestart() override;

private:

	void EnhancedInputMovement(const FInputActionValue& ActionValue);
	void EnhancedInputLook(const FInputActionValue& ActionValue);


};
