# OSS Widget
- 3개의 위젯을 Menu Switcher기능을 통해 하나의 Widget으로 구현


  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/fb50c00b-f11f-4d85-983b-5b32d0af4797)


*참고영상
- Host
    
  [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/cad827f9-9d86-455c-9b64-aea328ec0791)](https://youtu.be/e1t1-gyMnAc)
  
- Client  
  [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/239874c7-7a7f-49e3-a461-ede4e51325cf)](https://youtu.be/F0uGI3IhnkI)


### 구성된 OSS 위젯
 >   1. Main Menu Widget
 >   2. Host Session Menu Widget
 >   3. Join Session Menu Widget


## 1. Main Menu Widget
- Create 버튼을 누르면 [Host Session Menu Widget](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem_Widget.md#2-hostcreate-session-menu-widget)으로 Switch
- Join 버튼을 누르면 [Join Session Menu Widget](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem_Widget.md#3-join-session-menu-widget)으로 Switch
- 우측 상단 버튼을 누르면 게임종료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/8e16ca14-f650-45e4-8123-0c64a1c88a06)

## 2. Host Session Menu Widget
- Back Button을 누르면 [Main Menu Widget](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem_Widget.md#1-main-menu-widget)으로 Switch
- EditableBox에 제목을 입력 후 Create Button을 누르면 해당 제목을 가진 Game이 생성

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/cbc5f295-d4a3-42d7-9f66-017caa162631)

## 3. Join Session Menu Widget
- Back Button을 누르면 [Main Menu Widget](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem_Widget.md#1-main-menu-widget)으로 Switch
- ScrollBox에 생성된 Game이 있다면, 클릭 후 Join버튼을 클릭하면 Game에 Join

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/e93ca5f1-741e-43f9-a7f6-3830f578e2ac)
