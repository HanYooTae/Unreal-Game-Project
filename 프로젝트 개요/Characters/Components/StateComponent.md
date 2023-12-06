## 1. StateComponent

#### 캐릭터의 현재 상태를 나타내는 컴포넌트
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
