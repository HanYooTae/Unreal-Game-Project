# Unreal-Game-Project1

## 기본셋팅
1. 몽타주 레퍼런스 가져오기
   
   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/a9f0d4c4-8626-4bd3-a3de-2e96fbee9cc4)
     
2. Action Event 불러오기
   
   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/ba01eda7-79c7-4b7a-a713-7f7574dc5c70)

3. ParkourSystem 작동을 위한 변수

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/d2bc3f47-07ae-4d02-929c-184f7d3ed761)
   
   - FVector형 변수들은 닿는 물체의 Location, Normal vector를 저장하는데 사용합니다.


## Linetrace 소개
아래 그림 총 4개의 linetrace의 번호를 붙여 설명을 하겠습니다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/fcab60c9-f30c-42cb-8b42-650304082a0b)

- S는 Linetrace가 시작하는 곳이면 E는 Linetrace끝점(Parkour를 할수 있는 최소한의 사정거리)입니다.
  
### 1번 Linetrace
Start와 End의 값

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5d188c0e-866c-4a95-a672-784fe99b0555)

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/0ee9a629-4e45-43aa-8376-8d72d808a8fd)

무릎에 위치하는 1번 linetrace이며 Result값으로 FVector형 WallLocation, WallNormal의 값을 저장합니다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/08a9cdea-cc60-4484-beab-48a6d7ff9c87)

### 2번 Linetrace
* 2번 linetrace는 1번 linetrace가 정상작동후 실행되어야 하기 때문에 1번 linetrace의 result if문에 들어가있습니다.
  - 이어질 모든 Linetrace는 앞번호의 Linetrace result값이 true일때만 작동해야하므로 2번linetrace와 동일하게 윗번의 result if문 안에 작성되었습니다.








    
Start와 End의 값

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c07a950b-412b-402b-ac0d-b8c9bc05493c)

위에서 아래로 쏘고있는 Linetrace이며 Result값으로 FVector형 WallHeight의 값을 저장합니다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/b1a460bc-29af-437a-a686-09cbb717f2eb)

### 3번 Linetrace
Start와 End의 값

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/96085102-0f8a-4092-82e8-8e33c587d519)

위에서 아래로 쏘고있는 Linetrace이며 Result값으로 FVector형 WallHeight2의 값을 저장합니다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5973384c-73e4-47dd-ae52-878c85cd8b89)

### 4번 Linetrace
Start와 End의 값

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5e057ef4-b13f-4540-9881-2d8961da2549)

1번 Linetrace보다 조금 위에있으며 Result값으로 Canclimb인 bool변에 값을 true로 저장합니다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/ef804cb4-127a-4830-9300-c3d6a1f1cd77)

* 위그림의 player 모리위로 쏘는 Linetrace는 바로위에 막혀있는지에 대한 검사를 하며 현제 사용여부에 따라 result값 셋팅후 필요 여부에 따라 사용합니다.

## Linetrace의 Result값을 사용한 bool변수 셋팅
1. IsWallThick(물체의 두께를 학인하고 올라갈지 넘어갈지에 대한 bool변수)

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c1a8a021-caf6-4fe6-a79f-0fc37f6d5b3e)
  
2. ShouldPlayerClimb(점프를 통한 parkour 실행 bool변수)

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5c52659c-eef6-44ba-9c26-60b4fc0eee27)

- ShouldPlayerClimb의 값을 사용한 함수 호출

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/72991cf7-9968-4246-ac97-0a735ba99dba)

   *Jump와 Up은 아래에 설명되어있음
3. 4번 Linetrace의 Result값이 true라면 Canclimb = true

## Montage_Play
기본셋팅
- Montage_Play()함수 셋팅

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/24888e72-1d3f-418d-b5e9-a8ed1c9625c3)

   
- 몽타주가 플레이중일때는 bool변 IsClimbing = true로 저장 그후 Collision, Movement, ActorLocation 셋팅

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5f7e6b4b-03b4-4839-9df3-74bea54e9879)


## bool변수를 사용한 Montage_Play
### NextMontageYorN()
- SetTimer함수의 NextMontageYorN()
  IsWallThick가 true일때

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/e3fe6ecc-f19a-4d4d-9124-5f0d94b2d884)

  IsWallThick가 false일때

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/eda0ba43-64a5-4c81-83df-a643c0179151)

IsWallThick가 true일때는 Collision과 Movement를 다시 원상복구 해주며 false일때는 PlayJumpingDownMontage()와 Settimer싱행

### Jump()
- Canclimb가 true일때 준비된 PlayClimbMontage()함수가 실행되며 Delay를 대신할 SetTimer함수 사용

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6afa8daa-eb38-48cc-bd5f-baed60432745)

### Up()
- IsClimbing을 true값으로 저장
- IsWallThick변수가 true일때

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/abe9b82b-5e40-46ef-87c4-5e1aa5b41940)

- IsWallThick변수가 false일때

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/047c5d26-56e6-424e-83a6-3635f8df374a)

- IsWallThick if문이 끝나면 delay값주기

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/2a8c6fa2-ca4f-40f9-b92a-8a076dcd2f4d)

   *  LastCollision()

     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/0acb2b8e-8e8d-43b9-b4a3-8d5993321d86)

        

