## BehaviorComponent

#### Perception
감지를 위한 기능이다. 감지 거리, 감지된 대상을 가져올 수 있다.

+ Perception의 기본 셋팅

![image](https://github.com/user-attachments/assets/d7953175-9cd1-4927-bfa5-541c61d1ad50)


#### Behavior tree기능중 enemy의 mode를 컨트롤하는 컴포넌트
```
  void SetWaitMode();
  void SetApproachMode();
  void SetActionMode();
  void SetPatrolMode();
  void SetHittedMode();
  void SetAvoidMode();
```

- SetWaitMode : 정해진 시간 만큼 정지
- SetApproachMode : 플레이어가 감지되어 공격가능 거리에서 플레이어가 벗어날경우 플레이어에게 이동
- SetActionMode : 플레이어가 감지되어 공격
- SetPatrolMode : 플레이어를 감지하지 않은 상태에서 정해진 이동 경로를 따라 이동
- SetHittedMode : 플레이어에게 공격을 받았을때
- SetAvoidMode : 플레이어를 감지하지않은 상태

#### 샘플 영상

  [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/3f18b27a-a677-4220-9d5e-438bfc64a01f)
](https://youtu.be/owj9-RuassI)



