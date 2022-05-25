#include "EL_Character.h"

AEL_Character::AEL_Character()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEL_Character::BeginPlay()
{
	Super::BeginPlay();
}

void AEL_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEL_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

