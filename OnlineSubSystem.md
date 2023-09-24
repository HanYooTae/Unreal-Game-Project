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

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/269ce4b4-ccf5-45b0-923f-a16266625f36)

- Server Player가 Session Create를 성공했다면 맵 이동

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/3b4c0995-435a-48bb-9331-8ee589794738)


## 2. Destroy Session


## 3. Find Session


## 4. Join Session


## 5. Start Session && Game Mode
