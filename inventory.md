# Inventory System
inventorySystem을 구현하기 위해 2개의 component가 필요함 
1. InteractionComponent : Item의 정보를 Player에게 전달, 게임 요소들과의 상호작용으로 실행하는 기능 들을 가진 component (Player가 아닌 상호작용할 Object가 소유)
2. inventoryComponent : Item을 먹기, 버리기, 사용기능들을 가진 component

## Interaction System 구현

1. RefreshWidget : 아이템의 갯수 등 현 아이템의 상태를 알기위한 함수


2. BeginFocus, EndFocus : 플레이어 상호 작용 확인 추적이 이 Object에 대한 타격을 시작/종료할 때 클라이언트에서 호출
-UPrimitiveComponent : 충돌 데이터로 렌더링되거나 사용되는 일종의 형상을 포함하거나 생성하는 SceneComponent

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/0c577b11-6d8a-4a01-a55c-75a966f0becd)

3. BeginInteract, EndInteract, Interact : 플레이어가 Object와의 상호 작용을 시작 / 종료할 때 클라이언트에서 호출

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/53da5b9a-8ede-4016-842d-bd7772277276)

4. Line trace : player와 상호작욕을 할 Object를 감지하는 역할

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/79e67175-7d86-49f9-94e6-24ff87f90bcd)

- FoundNewInteractable     : 상호작용하는 물체를 찾았을 경우

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/def42b28-f526-498c-bc31-7fc39a901787)
  
- CouldnotFindInteractable : 상호작용 하는 물체를 찾지못할경우

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/dd764f6c-e247-4a91-8d1c-c308b361d754)

5. WB_InteractionCard
   -상호작용을 성공했을 경우 Object의 정보를 알 수 있는 Widget

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6e3bb2ac-87ec-46ef-93c5-72587de15caf)


## Inventory System 구현

### C++ class

1. FItemAddResult : 아이템의 갯수, 무게 Text 를 찍어주는 구조체

2. TryAddItem_Internal : TryAddItem(), TryAddItemFromClass()에서 호출하여 현 아이템의 상태를 체크하는 함수
*코드가 길기 때문에 일부 예시만 올림

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/4d3c63c9-0248-44ba-9f80-58d8e9a0b463)


4. AddItem : Items.Add()를 대신할 함수

5. OnInventoryUpdated : 인벤토리내부가 바뀌거나 UI가 업데이트가 될때 실행

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/1b288ce8-0ecf-4339-b2c8-f18ed62767f6)

5. TryAddItem : Inventory에 아이템 추가

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5e16a6a8-0314-49e4-9c15-6192dd08a976)

6. TryAddItemFromClass : 아이템 인스턴스 대신 아이템 클래스를 사용하여 인벤토리에 아이템 추가

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/eb30a73c-e613-4129-95e9-92a928f1d771)

7. ConsumeItem : 품목에서 일부 수량을 빼내고 수량이 0이 되면 재고에서 제거

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/a76654d2-5324-46de-95f8-e24a6b2e8c54)

8. RemoveItem : inventory 에서 Item제거

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/646f760a-93db-4872-9039-312f447af6aa)

9. HasItem : 아이템을 가지고 있다면 return값은 true

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/1ffd7e0e-ec52-423e-8f1f-c2ce339b9cf1)

10. FindItem : 얻은 아이템이 이미 가진 아이템의 class와 동일한지를 반환하는함수

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/2e307527-3238-498c-903f-94340b4cb5e6)

11. FindItemByClass : 모든 인벤의 아이템 클레스를 가져옴

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/b05ebdeb-125e-4f8c-9864-f06062710155)

### Widget BluePrint

1. WB_Inventory : WB_Inventory Widget, WB_DropWidget, WB_Equipment를 가진 main inventory widget

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c14b36c0-4c61-42ac-babd-b49c6e8c5d88)

2. WB_Inventory Widget : item을 먹으면 item thumbnail을 올려주며 item을 관리할 수 있는 widget
- Initialize From Inventory : On Inventory Updated 바인딩을 하여 자기자신을 최신화 하여 실행해주며 map형태의 변수 Item Widget 을 item class 의 아이템들을 저장하고 지워주는 함

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/b79be96d-59ba-488a-8771-07429bd7a416)

- UpdateInventory information : 인벤토리안에 아이템의 무게 갯수 를 표기해주는 함수

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/70cd884c-9bbe-4a8b-af4b-5b78cee792b4)
  
3. WB_DropWidget : 버릴 수량을 기임후 enter key를 누르면 입력한 갯수 만큼 버려주는 함수

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/43bbc6ed-633e-49fd-9c30-c0df6fe38645)


  참고영상 : https://youtu.be/5jAUMOePUg0


