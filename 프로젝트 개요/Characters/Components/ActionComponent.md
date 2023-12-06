## 4. ActionComponent

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

+ [데이터 에셋](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/DataAssets/DataAssets.md)을 사용하여 무기 장착을 시키고 있음.
