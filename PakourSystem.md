## ParkourSystem 구현

   - 총 4개의 LineTrace사용
     
   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c6bcc657-8483-45ee-b789-b3d07dcdebf9)


   * S는 Linetrace가 시작하는 곳이면 E는 Linetrace끝점(Parkour를 할수 있는 최소한의 사정거리)입니다.

   - LineTrace Result값 설명
      1. FVector형 WallLocation, WallNormal의 값을 저장
      2. FVector형 WallHeight의 값을 저장(이어질 모든 Linetrace는 앞번호의 Linetrace result값이 true일때만 작동해야하므로 2번linetrace와 동일하게 윗번의 result if문 안에 작성)
      3. WallHeight2의 값을 저장
      4. Canclimb인 bool변에 값을 true로 저장(player 머리위로 쏘는 Linetrace는 위에 막혀있는지에 대한 검사를 하며 현제 사용여부에 따라 result값을 셋팅)

1. Montage_Play

    몽타주를 실행하기전 작업
      - 몽타주 레퍼런스 가져오기(AnimInstance.h)
      
      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/69595733-851d-475d-a508-d28e7801fe6a)

      - Action Event 불러오기(CPlayer.h)

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c41d5ac6-2afc-4b08-b28d-40a415458f59)
   
      - Linetrace의 Result값을 사용한 bool변수 셋팅
          IsWallThick(물체의 두께를 학인하고 올라갈지 넘어갈지에 대한 bool변수)
           
         ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/293637d2-a93a-4cf6-9832-9be63c658097)

          ShouldPlayerClimb(점프를 통한 parkour 실행 bool변수)

         ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/67fc4031-faaf-4248-b688-ee6ec01cba82)

         *Jump와 Up은 아래에 설명되어있음
         
          4번 Linetrace의 Result값이 true라면 Canclimb = true

    Montage_Play
   
   - 재생하기위한 함수를 셋팅

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/8155ae47-4aa3-4ec3-9441-0b527749991c)


   - 재생 및 delay

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/ccf52393-f81d-47f2-b3e7-5e598d0a6030)


2. 기타 함수 소개
- NextMontageYorN(), LastCollision()
      
   - NextMontageYorN()
      *벽의 두깨의 정도를 저장한 변수 IsWallThick을 사용하여 각 다른 몽타주 재생

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/92402bb5-9619-464d-84ad-cae32fbb4729)

   - LastCollision()
      *Delay를 대신할 Settimer함수를 좀더 부드러운 몽타주 재생을 위한 콜리전 셋팅 함수
   
      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/ce55623c-f10a-4d1f-8be9-c488bc1ab6f0)
