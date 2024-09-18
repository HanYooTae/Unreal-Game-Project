## Interaction System 구현

- BeginInteract, EndInteract, BeginFocus, EndFocus, Interact
  + 상호작용후 작동 타이밍에 관한 이벤트 들이다.

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/80434b89-e684-4f9a-9bd1-fd2cbfc2aee2)

       begin focus    : 감지시작
       end focus      : 감지종료
       begin interact : 사용시작
       end interact   : 사용종료
       interact       : 사용
  
--------


#### Interact 감지 유/무의 결과값에 따라 나뉘는 함수

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/36673683-6a7f-461b-9c39-588ca582e95a)

+ ##### 함수 설명
  + performInteractionCheck   : tick함수에 위치하며 아래 두합수를 실행하는 함수  
  + CouldnotFindInteractable  : 상호작용할 물체가 없을 경우에 실행되는 함수
  + FoundNewInteractable      : 상호작용할 물체가 있을 경우에 실행되는 함수

--------

#### WB_InteractionCard
  - 상호작용을 감지했을 경우 Object의 정보를 알 수 있는 Widget

   
   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6e21658c-c8f9-4f18-9ecf-ebebe1e59430)
