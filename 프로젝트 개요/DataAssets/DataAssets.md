## Data Asset
- 만약 Player와 Enemy가 똑같은 무기를 사용한다면, Player 또는 Enemy 중 하나의 socket에 2개 이상의 Weapon이 Attach될 수 있으며, 그에 따라 하나의 Character에는 Weapon이 장착되지 않을 수 있음.

-  이를 방지하기 위하여 아래 작업 진행

- UObject를 상속받는 UCActionData_Spawned클래스를 생성하여 Weapon, Equipment, DoAction 변수를 생성

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/bf38072f-38b9-4247-b94c-2fa49b697e86)

- UDataAsset을 상속받는 UCActionData를 생성

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/8e605aae-a081-4a33-95ab-df5dcbaeefc7)

- Spawn시킨 asset들이 World에 올라왔는지 빠르고 편하게 확인하기 위하여 GetCustomLabel함수 생성

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/8b64be51-e347-4a23-aec6-c2c3b195353b)

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/b0d85ca9-d16a-4734-8153-73315d0b2008)
