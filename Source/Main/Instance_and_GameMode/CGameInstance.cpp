#include "Instance_and_GameMode/CGameInstance.h"
#include "Global.h"
#include "OnlineSessionSettings.h"

const static FName SESSION_NAME = L"GameSession";
const static FName KEY = L"SessionKey";

UCGameInstance::UCGameInstance(const FObjectInitializer& ObjectInitializer)
{
	CHelpers::GetClass(&MainMenuClass, "WidgetBlueprint'/Game/Widget/Menu/WB_MainMenu.WB_MainMenu_C'");
}

void UCGameInstance::Init()
{
	Super::Init();
	CLog::Print("GameInstace::Constructor Called");

	// OSS
	IOnlineSubsystem* oss = IOnlineSubsystem::Get();

	SessionInterface = oss->GetSessionInterface();
	
	if (!!oss)
	{
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnCreateSessionComplete);
		SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UCGameInstance::OnDestroySessionComplete);
	}
	else
	{
		CLog::Log("OSS Not Found!!");
	}
}

void UCGameInstance::Host(const FString& InSessionName)
{
	Current_SessionName = InSessionName;

	if (!!SessionInterface)
	{
		auto session = SessionInterface->GetNamedSession(SESSION_NAME);

		if (!!session)
			SessionInterface->DestroySession(SESSION_NAME);
		else
			CreateSession();
	}
}

void UCGameInstance::CreateSession()
{
	IOnlineSubsystem* oss = IOnlineSubsystem::Get();

	UE_LOG(LogTemp, Error, L"ING");

	if (!!SessionInterface)
	{
		FOnlineSessionSettings sessionSettings;

		if (oss->GetSubsystemName() == "NULL")
		{
			sessionSettings.bIsLANMatch = true;
		}
		else
		{
			sessionSettings.bIsLANMatch = false;
		}

		sessionSettings.NumPublicConnections = 2;
		sessionSettings.bShouldAdvertise = true;
		sessionSettings.Set(KEY, Current_SessionName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, sessionSettings);
	}
}

void UCGameInstance::OnCreateSessionComplete(FName InSessionName, bool bSuccess)
{
	UE_LOG(LogTemp, Error, L"CreateSessionComplete");

	// 技记 积己 角菩
	if (bSuccess == false)
	{
		CLog::Log("Could not create session!!");
		return;
	}

	// 技记 积己 己傍
	CLog::Log("Session Name : " + InSessionName.ToString());

	if (!!MainMenu)
		MainMenu->Detach();

	UWorld* world = GetWorld();
	CheckNull(world);
	
	world->ServerTravel("/Game/Map/Main?listen'");
}

void UCGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{
	UE_LOG(LogTemp, Error, L"DestroySessionComplete");

	if (bSuccess == true)
	{
		CreateSession();
	}
}

void UCGameInstance::LoadMenu()
{
	CheckNull(MainMenuClass);
	MainMenu = CreateWidget<UCMainMenu>(this, MainMenuClass);
	CheckNull(MainMenu);

	MainMenu->Attach();
}
