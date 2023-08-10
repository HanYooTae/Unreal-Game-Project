# Unreal-Game-Project1

## ParkourSystem 구현

	- 총 4개의 LineTrace사용
	![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/fcab60c9-f30c-42cb-8b42-650304082a0b)

	* S는 Linetrace가 시작하는 곳이면 E는 Linetrace끝점(Parkour를 할수 있는 최소한의 사정거리)입니다.

	- LineTrace Result값 설명
		1. FVector형 WallLocation, WallNormal의 값을 저장
		2. FVector형 WallHeight의 값을 저장(이어질 모든 Linetrace는 앞번호의 Linetrace result값이 true일때만 작동해야하므로 2번linetrace와 동일하게 윗번의 result if문 안에 작성)
		3. WallHeight2의 값을 저장
		4. Canclimb인 bool변에 값을 true로 저장(player 머리위로 쏘는 Linetrace는 위에 막혀있는지에 대한 검사를 하며 현제 사용여부에 따라 result값을 셋팅)

## Montage_Play

	- 몽타주를 실행하기전 작업
		1. 몽타주 레퍼런스 가져오기(AnimInstance.h)
		
		![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/a9f0d4c4-8626-4bd3-a3de-2e96fbee9cc4)

		2. Action Event 불러오기(CPlayer.h)

		![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/ba01eda7-79c7-4b7a-a713-7f7574dc5c70)
		
		3. Linetrace의 Result값을 사용한 bool변수 셋팅
			- IsWallThick(물체의 두께를 학인하고 올라갈지 넘어갈지에 대한 bool변수)
			![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c1a8a021-caf6-4fe6-a79f-0fc37f6d5b3e)

			- ShouldPlayerClimb(점프를 통한 parkour 실행 bool변수)

			![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/491a4799-bb65-4742-bd4e-067e09250a38)
			*Jump와 Up은 아래에 설명되어있음
			
			- 4번 Linetrace의 Result값이 true라면 Canclimb = true

	### Montage_Play
	
	- 재생하기위한 함수를 셋팅

		![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c222ba21-6355-46f9-81cc-744eba852930)

	- 재생 및 delay

		![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/481fc9e7-e593-4dfc-ab8b-4eb5482a0968)

## 기타 함수 소개
NextMontageYorN(), LastCollision()
		
	- NextMontageYorN()
		*벽의 두깨의 정도를 저장한 변수 IsWallThick을 사용하여 각 다른 몽타주 재생

		![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/bf8046f1-05d7-453d-90b7-e73d68fb47b8)

	- LastCollision()
		*Delay를 대신할 Settimer함수를 좀더 부드러운 몽타주 재생을 위한 콜리전 셋팅 함수
	
		![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/328e9ef3-a175-4eed-b7a4-1c05a58d3759)
