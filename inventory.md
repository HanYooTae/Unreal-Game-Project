# Inventory System
inventorySystem을 구현하기 위해 2개의 component가 필요함 
1. InteractionComponent : Item의 정보를 Player에게 전달, 게임 요소들과의 상호작용으로 실행하는 기능 들을 가진 component (Player가 아닌 상호작용할 Object가 소유)
2. inventoryComponent : Item을 먹기, 버리기, 사용기능들을 가진 component

## Interaction System 구현

1. RefreshWidget : 아이템의 갯수 등 현 아이템의 상태를 알기위한 함수

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/12303e2d-4d4a-44cf-8533-505b81ed31a0)

2. BeginFocus, EndFocus : 플레이어 상호 작용 확인 추적이 이 Client에 대한 타격을 시작/종료할 때 클라이언트에서 호출
-UPrimitiveComponent : 충돌 데이터로 렌더링되거나 사용되는 일종의 형상을 포함하거나 생성하는 SceneComponent

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/0c577b11-6d8a-4a01-a55c-75a966f0becd)

3. BeginInteract, EndInteract, Interact : 플레이어가 Client와의 상호 작용을 시작 / 종료할 때 클라이언트에서 호출

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/53da5b9a-8ede-4016-842d-bd7772277276)

4. Line trace : player와 상호작욕을 할 Object를 감지하는 역활

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/79e67175-7d86-49f9-94e6-24ff87f90bcd)

- FoundNewInteractable     : 상호작용하는 물체를 찾았을 경우

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/def42b28-f526-498c-bc31-7fc39a901787)
  
- CouldnotFindInteractable : 상호작용 하는 물체를 찾지못할경우

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/dd764f6c-e247-4a91-8d1c-c308b361d754)


## Inventory System 구현

  참고영상 : https://youtu.be/5jAUMOePUg0


