# Interaction and Inventory System
## Interaction System 구현
####1. 상호작용을 위한 감지 시스템
- player 카메라의 중점에서 시작 되어 InteractionCheckDistance(3000.f)만큼을 탐지하는 linetrace

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/2a563fe9-81ed-4f58-8cf4-9b42732e586e)

*로컬이거나 인터렉트하고 있는지 그리고 상호작용 빈도수가 마지막으로 상호작용을 시도한 타임보다 작은지를 조건으로하여 performInteractionCheck(linetrace) 호출

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/3c6a2797-c622-426b-94cb-4c782c75be1a)


-  FoundNewInteractable : interact가능 object와 충돌시 나오는 함수이며 충돌체를 interaction중 충돌체의 class를 확인하고 마지막 충돌체를 최신화 한다.
-  CouldnotFindInteractable : interact가능 object를 찾지 못할 경우 타이머 헨들을 초기화 해주며 저장했던 상호작용 object들을 삭제한다.

####2. interaction widget
-  interact성공한 object가 CPickup class안의 InitializePickup함수를 통해 정보를 위젯으로 스폰한다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/41f49f65-f36c-4293-97e6-c5c07293dc45)

*MarkDirtyForReplication() : 개체를 복제가 필요한 것으로 표시 하 함수. 복제된 속성을 수정한 후에는 이를 내부적으로 호출

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/77b3dad7-0622-4f67-af50-675677f30cea)


####3. Pickup System
- interactionComponent를 가지는 object, 아이템, 장애물, 조형물등 여러 방면으로 쓰여질 class
- 상호작용을 하는 object spawn 그리고 일부 아이템을 주울때 다른 유저와 같이 interact하는지에 대한 검사를 담당


## Inventory System 구현

  참조영상 : https://youtu.be/5jAUMOePUg0
