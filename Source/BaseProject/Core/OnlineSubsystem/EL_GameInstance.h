#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "EL_GameInstance.generated.h"

class FOnlineSessionSearch;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFindGameSessionsComplete, int32, TotalSessions);

UCLASS()
class BASEPROJECT_API UEL_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintAssignable)
		FOnFindGameSessionsComplete OnFindGameSessionsComplete;

	UFUNCTION(BlueprintCallable)
		void HostGameSession();
	UFUNCTION(BlueprintCallable)
		void FindGameSessions();
	UFUNCTION(BlueprintCallable)
		void JoinGameSession();

	virtual void Init() override;
	void OnCreateSessionComplete(FName SessionName, bool bSucceded);
	void OnFindSessionsComplete(bool bSucceded);

private:

	void StartFinding();

	IOnlineSessionPtr SessionInterface;
	TArray<FOnlineSessionSearchResult> SearchResults;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	FTimerHandle FindSearchTimer;
	
};
