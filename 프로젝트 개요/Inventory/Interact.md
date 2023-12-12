## Interaction System 구현

- BeginInteract, EndInteract, Interact : 플레이어가 Object와의 상호 작용을 시작 / 종료할 때 클라이언트에서 호출

  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/80434b89-e684-4f9a-9bd1-fd2cbfc2aee2)


- Line trace : player와 상호작욕을 할 Object를 감지하는 역할
hitresult에 따라 FoundNewInteractable, CouldnotFindInteractable 호출

  - FoundNewInteractable     : 상호작용하는 물체를 찾았을 경우 
  - CouldnotFindInteractable : 상호작용 하는 물체를 찾지못할경우


- WB_InteractionCard
   -상호작용을 성공했을 경우 Object의 정보를 알 수 있는 Widget

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6e3bb2ac-87ec-46ef-93c5-72587de15caf)


* 참고영상

    

  * 참고영상 

   [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/299b5704-51ff-42ce-92ef-3f35f27e163b)
](https://youtu.be/lKYUg1sQXCo)
