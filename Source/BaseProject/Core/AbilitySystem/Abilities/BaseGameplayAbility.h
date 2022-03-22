#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../../BaseData.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BASEPROJECT_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UBaseGameplayAbility() = default;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		EBaseAbilityInputId AbilityInputID = EBaseAbilityInputId::None;
	
};
