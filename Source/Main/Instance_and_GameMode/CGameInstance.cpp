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
	CLog::Print("GameInstace::Constructor Called");
	
	IOnlineSubsystem* oss = IOnlineSubsystem::Get();

	SessionInterface = oss->GetSessionInterface();

	if (SessionInterface.IsValid())
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnDestroySessionComplete);
	}
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
	DesiredSessionName = InSessionName;

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
		}

		sessionSettings.NumPublicConnections = 4;
		sessionSettings.bShouldAdvertise = true;
		sessionSettings.Set(SESSION_SETTINGS_KEY, DesiredSessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, sessionSettings);
	}
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

	//-> Everybody Move to Play Map
	world->ServerTravel("/Game/Map/Main?listen");
}

void UCGameInstance::OnDestroySessionComplete(FName InSessionName, bool InSuccess)
{
	UE_LOG(LogTemp, Error, L"DestroySessionComplete");

	if (InSuccess == true)
		CreateSession();
}