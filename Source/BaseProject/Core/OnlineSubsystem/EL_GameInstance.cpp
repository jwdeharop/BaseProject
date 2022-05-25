#include "EL_GameInstance.h"
#include "OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"

void UEL_GameInstance::HostGameSession()
{
	if (SessionInterface)
	{
		FOnlineSessionSettings SessionSettings;

		SessionSettings.bIsDedicated = false;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.NumPublicConnections = 4;

		SessionInterface->CreateSession(0, "Elemental", SessionSettings);
	}
}

void UEL_GameInstance::FindGameSessions()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = true;
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UEL_GameInstance::JoinGameSession()
{
	if (SearchResults.Num() > 0)
	{
		SessionInterface->JoinSession(0, *SearchResults[0].GetSessionIdStr(), SearchResults[0]);
	}
}

void UEL_GameInstance::Init()
{
	Super::Init();

	if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			GetTimerManager().SetTimer(FindSearchTimer, this, &UEL_GameInstance::StartFinding, 5.f, true);
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,
				&UEL_GameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this,
				&UEL_GameInstance::OnFindSessionsComplete);
		}
	}
}

void UEL_GameInstance::OnCreateSessionComplete(FName SessionName, bool bSucceded)
{
	if (bSucceded)
	{
		UE_LOG(LogTemp, Error, TEXT("Session Created succesfuly"));
	}
}

void UEL_GameInstance::OnFindSessionsComplete(bool bSucceded)
{
	if (bSucceded)
	{
		SearchResults = SessionSearch->SearchResults;
	}
	else
	{
		SearchResults.Empty();
	}

	OnFindGameSessionsComplete.Broadcast(SearchResults.Num());
}

void UEL_GameInstance::StartFinding()
{
	FindGameSessions();
}
