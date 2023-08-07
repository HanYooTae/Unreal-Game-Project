# Unreal-Game-Project1

## 4개의 LineTrace
1. Owner Charater전방으로 4개의 linetrace를 쏜다.
   CParkourSystem.cpp
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/21015234-55ca-4ea8-a970-decb153edfed)
  - 사용한 함수 
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5837157a-7c62-4502-a2e2-9527bb49c80e)

## Play Montage
1. Create Parkour Actor Component
   CPlayer.cpp
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/2c8aae0c-a4a4-4390-b456-a65e308a2cdc)
    함수 소개(CHelpers.h)
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/1320502b-7e1e-49bb-8313-da16d385f2f0)

2. Montage
   CAnimInstance.h
  - 레퍼런스 저장 변수
    * ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/ccc55a32-4e7d-4269-80e5-578421576993)
  - 레퍼런스 가져오기
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/e80bbc79-bec5-45ec-ac34-a3c2266eac22)
  - Play Montage    
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/d434a9d7-e5b3-46bf-af2c-dc61425599ec)

3. Play
   CParkourSystem.cpp
   - play전 Owner Charater의 위치조정, collisionEnabled, MovementMode 
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/253c3d98-2f10-4975-afc8-9f640fe927f5)
   - Play
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/839c46a0-b0e5-4738-8800-655ff37b2144)
   - 재생후 delay
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6b392a52-b619-4a42-81b8-953022637e78)
