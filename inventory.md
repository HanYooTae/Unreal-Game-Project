# Inventory System 구현

1. 상호작용 가능한 오브젝트
- 상호작용을 위한 InteractComponent 생성
InteractComponent를 가진 오브젝트가 무엇인지 그리고 player, Item과의 상호작용 상태를 확인하기위한 Component
- PlayerCameraLineTrace
PlayerCamera의 시작되는 LineTrace로 InteractComponent를 가진 오브젝트를 찾는다.
- Interact할 물체 정보창Widget 생성
LineTrace에서 찾은 오브젝트가 InteractComponent를 가졌다면 해당 오브젝트의 정보창, 기능, 갯수 등을 표기한 정보창 spawn

2. InventoryComponent 생성
- Item, FoodItem(Item을 상속받은) C++ 클래스 생성
  게임중 이름, 설명, 무게, 중복소유가능여부, 총 소유갯수 포함
- Interact하여 Item일경우 Data를 가져와 InventoryWidget으로 data를 전달

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/fc879561-9053-4963-a84f-561c3bc04492)


3. Gun(Item Mesh)
- Item Mesh, Thumbnail 사진첨부

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/b44a4bd7-6be2-47c8-8adf-9a6adf4a2ff5)

4. Drop, use System구현
 (구현에앞서 Object를 멀티 플레이중 복제 하기위한 함수 SetIsReplicated가 4.27버전으로 올라오면서 SetIsReplicatedByDefault으로 사용해야함)
- Drop : Item을 버리는 작업을 수행하는 함수. Inventory내부 Item Slot 옆으로 Item Thumbnail을 드레그하여 마우스 키를 때면 World상에 Spawn
- Use : 각 아이템내부 클레스의 Use함수호출하여 각 아이템의 역활 수행 ex) FoodItem::Use (){CLog::Print("we ate some posion. ><");}

5. 원하는 수량을 버리는 기능
- Drop Widget를 추가하여 원하는 수량을 입력

  참조영상 : https://youtu.be/5jAUMOePUg0
