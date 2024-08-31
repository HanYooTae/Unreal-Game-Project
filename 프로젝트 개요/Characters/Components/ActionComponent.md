## ActionComponent

####  캐릭터가 장착한 무기를 관리하는 컴포넌트

```
  UENUM(BlueprintType)
  enum class EStateType : uint8
  {
	  Unarmed, Fist, Sword, Sniper
  };
```
- Unarmed : 캐릭터가 무기를 장착하지 않은 상태
- Fist : 캐릭터가 주먹과 발차기를 사용할 수 있는 상태
- Sword : 캐릭터가 검을 사용할 수 있는 상태
- Sniper : 캐릭터가 총을 사용할 수 있는 상태

--------------

+ 데이터 에셋을 사용하여 무기 장착을 시키고 있음.

	![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/e47c6b68-40f8-4d7f-a5a0-3441dd75ebc0)
