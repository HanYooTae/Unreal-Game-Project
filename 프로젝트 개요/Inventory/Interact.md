## Interaction System 구현

- BeginInteract, EndInteract, BeginFocus, EndFocus, Interact
  + 상호작용후 작동 타이밍에 관한 이벤트 들이다.

![image](https://github.com/user-attachments/assets/9cc9416b-3711-4c41-b10c-dfca12c5b954)
 
       begin focus    : 감지시작
       end focus      : 감지종료
       begin interact : 사용시작
       end interact   : 사용종료
       interact       : 사용
 

--------

#### WB_InteractionCard
  - 상호작용을 감지했을 경우 Object의 정보를 알 수 있는 Widget

![image](https://github.com/user-attachments/assets/f036ee5c-606c-4fac-b065-7b8d29137180)

