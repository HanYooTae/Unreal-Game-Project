# Create OnlineSubSystem (한유태)
- MultiPlay Game을 만들기 위해서 OnlineSubSystem(OSS)를 사용.
- 2인용 프로젝트기 때문에 Listen Server로 구현.
- OSS를 구성하기 위해서는 인터페이스 함수인 IOnlineSubsystem을 사용해야 함.
- 각각의 역할을 가지고 있는 함수들(Create, Destroy, Find, Join)이 마무리되었을 때 호출되는 함수들이 필요

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/f40c1d45-74be-4000-82cf-c590024b3827)





## 1. Create Session
- OSS를 사용하려면 FOnlineSessionSettings클래스를 사용해야 함.
- FOnlineSessionSettings클래스를 통해서 아래와 같은 정보들을 Setting할 수 있다.
  
  -> Accepted Player Numbers
  
  -> Advertised Session or not
  
  -> Lan Match Session or not
  
  -> etc.

- CMainMenu.cpp

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/a57da47e-9de2-4666-9457-175efdbb9fd7)

- Server Player가 Session Create를 성공했다면 맵 이동

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/3b4c0995-435a-48bb-9331-8ee589794738)


## 2. Destroy Session
- Session을 Create한 후에 종료하더라도 세션은 그대로 남아있기 때문에 Session을 Create할 수 없음.
- 기존에 만들어져 있던 Session을 Destroy해야 다시 Create할 수 있음.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/b532b3df-bb8d-4a96-b0f8-7e5e4b580614)

- Session Destroy가 완료되었다면 Session을 Create

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/783570b5-779e-49a1-978c-12e354d98d19)


## 3. Find Session
- 만들어진 Session을 검색하려면,

  -> IOnlineSession::FindSessions함수를 사용

  -> 검색하려는 레퍼런스를 FOnlineSessionSearch로 전달

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/573e5361-54bc-4899-80b9-6e132d20eef5)

  
- FOnlineSessionSearch->SearchResults멤버가 일치하는 세션으로 채워짐.
- CreateSession에서 Setting한 Key값과 Name을 FOnlineSessionSearch로 전달받음.
- Session Find가 완료되면 MainMenu의 Scrollbox에 Session이 조회됨.(https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/OnlineSubSystem_Widget.md#3-join-session-menu-widget)

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/0a454c4a-0937-4868-a356-66aa16f7a72c)


  



## 4. Join Session


## 5. Start Session && Game Mode
- 추후 진행 예정
