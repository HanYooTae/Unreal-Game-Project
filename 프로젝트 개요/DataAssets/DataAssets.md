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


- 월드 상에 Spawn시킬 DataAsset의 부품들을 담은 BeginPlay함수

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/343014b6-fc84-43b6-87b7-0e9fe5661fc9)
  [CWeapon](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/DataAssets/CWeapon.md)

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/e577d64b-c8a3-49fa-9567-eddc6768655a)
  [CEquipment](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/DataAssets/CEquipment.md)



  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/9fa70967-e722-477f-ab8f-eaea5cf360d8)
  [CDoAction](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/DataAssets/CDoAction.md)


