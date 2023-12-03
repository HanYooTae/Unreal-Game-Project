# RPC 환경을 위해 작성한 코드 목록

## CInventoryComponent

- ClientRefreshInventory() : 인벤토리 새로고침 역할 개인의 인벤토리만 새로고침 할수 있도록함

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/7b4a9a0f-9986-474f-87da-1970cfa643b9)


## UCParkourSystem

- Parkour() : 함수의 서버역할, 플레이어 V키를 누르면 실행되는 함수

- Vault(), Jump(), NextMontageYorN() : LineTrace 검사에 맞게 Montage재생

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/137d1211-35de-4c1a-9ec8-4d6b7efcb3af)


## CInteractionComponent

- RefreshWidget() : 상호작용중 (아이템의 갯수 등 현 아이템의)상태를 알기위한 함수

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5cd5be08-eab1-4bf7-9fb5-58dc4c9e8352)


## CActionComponent

- SetMode() : Mode를 바꿔주는 함수

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5701fd3b-a467-4a29-b5ed-ac86a00f945c)


## CPlayer

- PerformInteractionCheck() : 아래 두 함수 를 실행하는 함수
- CouldnotFindInteractable() : 상호작용 하는 물체를 찾지못할경우
- FoundNewInteractable() : 상호작용하는 물체를 찾았을 경우

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/727c8b9a-b460-4bf3-82d7-542d25d2736e)

- OnAction() : DoAction()함수 호

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/817df7ff-ce1e-416a-a896-c171b80ebbf0)

-SeverBeginInteract(), SeverEndInteract() : 상호작용 시작할때, 끝날때 호출함수

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6eb0d5a8-a151-4e8f-b03b-922d03026c7a)

- On() : 각 공격Mode Change함수

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/56a09998-4168-432c-a811-64160a3bb5b0)

- UseItem() : inventory에서 아이템을 사용할때

* 사진 자료

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/7103d060-3c48-49cc-9de7-c03a9a55b45d)
  
- DropItem() : 아이템을 버릴때

*사진 자료 

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/abfa0b79-fd29-43d0-a0dc-7e37a55bcc36)


