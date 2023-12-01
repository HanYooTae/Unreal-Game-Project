#### Data Asset
-> 만약 Player와 Enemy가 똑같은 무기를 사용한다면 Player 또는 Enemy 중 하나의 socket에 2개 이상의 Weapon이 Attach됨. 이를 방지하기 위하여 아래 작업 진행

-> UObject를 상속받는 UCActionData_Spawned클래스를 생성하여 Weapon, Equipment, DoAction 변수를 생성

-> UDataAsset을 상속받는 UCActionData를 생성

-> UCActionData를 UCActionData_Spawned의 Friend class로 지정하여 Weapon, Equipment, DoAction을 사용

- UCActionData_Spawned

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/bf38072f-38b9-4247-b94c-2fa49b697e86)

- UCActionData

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/5714af02-24e1-43f0-baba-04d0e4d2fc25)

ex) DA_Sniper

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/6d034db7-f4d1-4f5b-9d41-7503cadeb0a7)
