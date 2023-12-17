#include "Instance_and_GameMode/CGameInstance.h"
#include "Global.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = L"GameSession";
const static FName SESSION_SETTINGS_KEY = TEXT("SessionKey");

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&MainMenuClass, "WidgetBlueprint'/Game/Widget/Menu/WB_MainMenu.WB_MainMenu_C'");
}

void UCGameInstance::Init()
{
	Super::Init();
	//CLog::Print("GameInstace::Constructor Called");
	
	IOnlineSubsystem* oss = IOnlineSubsystem::Get();

	if (!!oss)
	{
		SessionInterface = oss->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UCGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnJoinSessionComplete);
		}
	}

	else
		CLog::Log("OSS Not Found!!");

	if (!!GEngine)
		GEngine->OnNetworkFailure().AddUObject(this, &UCGameInstance::OnNetworkFailure);
}

void UCGameInstance::LoadMenu()
{
	CheckNull(MainMenuClass);
	MainMenu = CreateWidget<UCMainMenu>(this, MainMenuClass);
	CheckNull(MainMenu);

	MainMenu->Attach();
}

void UCGameInstance::Host(const FString& InSessionName)
{
	SessionName = InSessionName;

	if (SessionInterface.IsValid())
	{
		auto session = SessionInterface->GetNamedSession(SESSION_NAME);

		if (!!session)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UCGameInstance::ReturnToMainMenu()
{
	APlayerController* controller = GetFirstLocalPlayerController();
	CheckNull(controller);
	controller->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::CreateSession()
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings sessionSettings;

		if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
		{
			sessionSettings.bIsLANMatch = true;
			sessionSettings.bUsesPresence = false;
		}
		else
		{
			sessionSettings.bIsLANMatch = false;
			sessionSettings.bUsesPresence = true;
			sessionSettings.bUseLobbiesIfAvailable = true;
		}

		sessionSettings.NumPublicConnections = 4;
		sessionSettings.bShouldAdvertise = true;
		sessionSettings.Set(SESSION_SETTINGS_KEY, SessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, sessionSettings);
	}
}

void UCGameInstance::FindSession()
{
	SearchSettings = MakeShareable(new FOnlineSessionSearch());
	
	if (SearchSettings.IsValid())
	{
		CLog::Log("Starting Find Session");

		SearchSettings->bIsLanQuery = false;
		SearchSettings->MaxSearchResults = 100;
		SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

		SessionInterface->FindSessions(0, SearchSettings.ToSharedRef());
	}
}

void UCGameInstance::JoinSession(uint32 InSessionIndex)
{
	CheckFalse(SessionInterface.IsValid());
	CheckFalse(SearchSettings.IsValid());

	if (!!MainMenu)
		MainMenu->Detach();

	SessionInterface->JoinSession(0, SESSION_NAME, SearchSettings->SearchResults[InSessionIndex]);
}

void UCGameInstance::StartSession()
{
	CheckFalse(SessionInterface.IsValid());
	SessionInterface->StartSession(SESSION_NAME);
}

void UCGameInstance::OnCreateSessionComplete(FName InSessionName, bool InSuccess)
{
	UE_LOG(LogTemp, Error, L"CreateSessionComplete");

	// 技记 积己 角菩
	if (InSuccess == false)
	{
		CLog::Log("Could not create Session!!");
		return;
	}

	// 技记 积己 己傍
	CLog::Log("Session Name : " + InSessionName.ToString());

	if (!!MainMenu)
		MainMenu->Detach();

	CLog::Print("Host");

	UWorld* world = GetWorld();
	CheckNull(world);

	//-> Move to Play Map
	world->ServerTravel("/Game/Map/Main?listen");
}

void UCGameInstance::OnDestroySessionComplete(FName InSessionName, bool InSuccess)
{
	UE_LOG(LogTemp, Error, L"DestroySessionComplete");

	if (InSuccess == true)
		CreateSession();
}

void UCGameInstance::OnFindSessionsComplete(bool InSuccess)
{
	if (InSuccess == true && SearchSettings.IsValid() && !!MainMenu)
	{
		TArray<FSessionData> foundSession;

		CLog::Log("Finished Find Session");

		CLog::Log("========<Find Session Results>========");
		for (const auto& sessionsearch : SearchSettings->SearchResults)
		{
			FSessionData data;

			data.MaxPlayers = sessionsearch.Session.SessionSettings.NumPublicConnections;
			data.CurrentPlayers = data.MaxPlayers - sessionsearch.Session.NumOpenPublicConnections;
			data.HostUserName = sessionsearch.Session.OwningUserName;

			FString sessionName;
			if (sessionsearch.Session.SessionSettings.Get(SESSION_SETTINGS_KEY, sessionName))
			{
				data.SessionName = sessionName;
				CLog::Log("SessionID : " + sessionName);
				CLog::Log("Ping : " + FString::FromInt(sessionsearch.PingInMs));
			}
			else
			{
				CLog::Log("Cannot found Session Setting Key");
			}

			foundSession.Add(data);

			MainMenu->SetSessionList(foundSession);
		}

	}

}

void UCGameInstance::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type InResult)
{
	FString address;

	if (SessionInterface->GetResolvedConnectString(InSessionName, address) == false)
	{
		switch (InResult)
		{
		case EOnJoinSessionCompleteResult::SessionIsFull:
			CLog::Log("SessionIsFull");
			break;
		case EOnJoinSessionCompleteResult::SessionDoesNotExist:
			CLog::Log("SessionDoesNotExist");
			break;
		case EOnJoinSessionCompleteResult::CouldNotRetrieveAddress:
			CLog::Log("CouldNotRetrieveAddress");
			break;
		case EOnJoinSessionCompleteResult::AlreadyInSession:
			CLog::Log("AlreadyInSession");
			break;
		case EOnJoinSessionCompleteResult::UnknownError:
			CLog::Log("UnknownError");
			break;
		}
		return;
	}

	APlayerController* controller = GetFirstLocalPlayerController();
	CheckNull(controller);
	
	//CLog::Print("Address is " + address);

	controller->ClientTravel(address, ETravelType::TRAVEL_Absolute);
}

void UCGameInstance::OnNetworkFailure(UWorld* InWorld, UNetDriver* InNetDriver, ENetworkFailure::Type InFailureReason, const FString& InErrorMessage)
{
	CLog::Print("Network Error Message : " + InErrorMessage);

	ReturnToMainMenu();
}
