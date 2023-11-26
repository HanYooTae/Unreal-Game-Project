# Create Components
- Characters(Player, Enemy)를 구성하는 컴포넌트들을 역할별로 나누어 생성.

- 구성된 Components
  1. CStateComponent
  2. CStatusComponent
  3. CMontagesComponent
  4. CActionComponent


## 1. CStateComponent

#### Character의 현재 상태를 나타내는 컴포넌트
- Idle(아무것도 안하는 상태)
- Equip(무기를 장착하는 상태)
- Action(공격하는 상태, 장착한 무기타입에 따라 공격하는 몽타주가 상이함)
- Hitted(Character가 공격에 맞은 상태)
- Dead(Character가 죽은 상태)
  
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/ac300712-0313-4cb6-80fa-9b2c87fa7215)


#### FStateTypeChangedSignature라는 델리게이트를 생성하여 Character의 상태를 변화시킴
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/87dfc344-52e5-4b54-b205-9bc71284b417)

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/2e5ab983-47d8-4e3e-9009-6ba579f3a7b1)

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/56f3a402-c60c-40be-9279-5dfa1c654e63)
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/b3a79a0a-ba26-4206-be88-4dd1c4545d07)


## 2. CStatusComponent

#### Character의 이동능력 및 HP를 나타내는 컴포넌트

- Character의 이동속도, 최대 체력, 이동능력, 현재 체력
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/0d8fee6a-0c62-4a61-9983-cf682cf44541)

- Enum으로 정의한 이동속도 Sneak(200), Walk(400), Run(600)
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/418a757f-0541-4f72-8014-039c65d9b447)
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/e9baf471-931a-44bd-b651-c4a5c1356b08)

- 이동능력 정의 (움직일 수 있는가, 움직일 수 없는가)
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/a04b9bdb-0cff-4fe8-9caf-833c5d30135c)

- 체력 상태 정의
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/80fcbf1d-c883-4615-8c28-dbe9fd609c11)



## 3. CMontagesComponent


## 4. CActionComponent

