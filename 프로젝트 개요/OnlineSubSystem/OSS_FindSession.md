## 3. Find Session
+ 만들어진 Session을 검색하려면,

  + IOnlineSession::FindSessions함수를 사용
  + 검색하려는 레퍼런스를 FOnlineSessionSearch로 전달

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/573e5361-54bc-4899-80b9-6e132d20eef5)

- FOnlineSessionSearch->SearchResults멤버가 일치하는 세션으로 채워짐.
- CreateSession에서 Setting한 Key값과 Name을 FOnlineSessionSearch로 전달받음.
- Session Find가 완료되면 MainMenu 위젯에 조회됨.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/0a454c4a-0937-4868-a356-66aa16f7a72c)
