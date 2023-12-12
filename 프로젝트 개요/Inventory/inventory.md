## Inventory System 구현

### C++ class

1. 아이템의 갯수, 무게 Text 를 표기

2. 현 아이템의 상태를 체크하는 함수

3. 새로고침

4. Inventory에 아이템 추가

5. 인벤토리에 아이템 추가
   
6. inventory 에서 Item제거

### Widget BluePrint

1. WB_Inventory : WB_Inventory Widget, WB_DropWidget, WB_Equipment를 가진 main inventory widget

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/c14b36c0-4c61-42ac-babd-b49c6e8c5d88)

2. WB_Inventory Widget : item을 먹으면 item thumbnail을 올려주며 item을 관리할 수 있는 widget
- 기능
  1. Widget을 최신화 하여 실행해주며 아이템들을 저장하고 지워주는 함

  2. 인벤토리안에 아이템의 무게 갯수 를 표기

  3. 버릴 수량을 기임후 enter key를 누르면 입력한 갯수 만큼 버림



  * 참고영상 

   [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/299b5704-51ff-42ce-92ef-3f35f27e163b)
](https://youtu.be/lKYUg1sQXCo)
