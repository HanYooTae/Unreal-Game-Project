## 3. Find Session
+ 만들어진 Session을 검색하려면,

  + IOnlineSession::FindSessions함수를 사용
  + 검색하려는 레퍼런스를 FOnlineSessionSearch로 전달

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/573e5361-54bc-4899-80b9-6e132d20eef5)

- FOnlineSessionSearch->SearchResults멤버가 일치하는 세션으로 채워짐.
- CreateSession에서 Setting한 Key값과 Name을 FOnlineSessionSearch로 전달받음.
- Session Find가 완료되면 MainMenu의 Scrollbox에 [Session](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem_Widget.md#3-join-session-menu-widget)이 조회됨.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/0a454c4a-0937-4868-a356-66aa16f7a72c)
