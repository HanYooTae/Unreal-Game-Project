## 1. StateComponent

#### 캐릭터의 현재 상태를 관리하는 컴포넌트
```
  UENUM(BlueprintType)
  enum class EStateType : uint8
  {
	  Idle, Equip, Action, Hitted, Dead
  };
```

- Idle : 캐릭터가 아무것도 하지 않는 상태 (움직이는 상태 제외)
- Equip : 캐릭터가 무기를 장착 또는 해제하는 상태
- Action : 캐릭터가 공격하는 상태
- Hitted : 캐릭터가 피격되는 상태
- Dead : 캐릭터의 HP가 0인 상태

  * 참고 영상
    
  [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/5b6806a1-4e7b-46ca-9834-5a0659fb45be)](https://youtu.be/M6us0ah3zBw)
