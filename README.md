# Unreal Game Team Project
### 프로젝트 완성 시 전체적으로 수정할 내용입니다.
### 지금은 단순히 주차별 진행도만 나열되어 있습니다.

## 1주차
**1. 에셋 임포트** 
원하는 기능들이 구현이 된다면 다른 부가적인 게임요소들을 접목시킬 예정입니다.




**2. 어떤 게임을 만들 것인가**
구체적인 계획은 나오지 않았습니다.
할 수 있는 모든 기능을 구현하는 것에 관점을 둘 예정입니다.
오픈 월드 형식으로 (EX. GTA) 한 맵에 몰아서 기능을 구현할 예정입니다. 

**첨부 사진(작업진행 구성도)**

![Image](https://github.com/simeddk/HellWorld/assets/41534351/48a75a31-7789-458b-baea-7a290ef64b0e)

파쿠르, 지도, 인벤토리, 등 여러 새로운 기능들을 구현할 예정입니다.



3. 예상되는 기술적 요소
(현재 진행상황)

**<Parkuor>**


1) 무릎 높이의 character forward 방향의 LineTrace

2) 제자리에서 올라갈수 있는가의 LineTrace

3) 벽의 두꺼운 정도를 알아낼 LineTrace

4) 점프한 높이의 LineTrace (점프x = false, 점프o = true)



**<Map & Compass>**


1) WB_Minimap 생성
 - Character를 따라오는 TopView 시점의 카메라로  Minimap을 찍도록 구성

2) WB_Compass 생성
 - 플레이어가 어느 방향을 가르키는지 상단 UI를 통해 볼 수 있도록 구성

3) WB_MainGUI
 - WB_Minimap과 WB_Compass를 MainGUI에 붙여서 사용
 - 추후, 다른 UI가 필요하다면 MainGUI에 붙일 예정




**4. 플레이어 캐릭터의 기본 기능 만들 것**
(영상 youtube 주소)
https://www.youtube.com/watch?v=2mUt0p7I1i0


## 2주차
유태 - 왼쪽 하단 Minimap 및 상단 Compass UI 구현
현범 - Parkour 시스템 구현

**현재 진행 상황**
 - Parkour 시스템(BluePrint)에 구현한 UI 붙여넣은 상태

**목표**
 - (유태) UI 디자인 간소화
 - (현범) Parkour 시스템 C++로 구현

https://youtu.be/5w58z5KOIaM


## 3, 4주차
1. 이번주에 한 것
https://www.youtube.com/watch?v=oI6YeIkRpdE

2. 스크린샷


![Image](https://github.com/simeddk/HellWorld/assets/41534351/0d48695d-2815-42a2-bb6c-c3d474bd1cb8)




![Image](https://github.com/simeddk/HellWorld/assets/41534351/74e04a5e-b5be-4239-908f-41c86288facd)



3. 고찰 및 다음주 할 것
- (유태) 캐릭터 배속 구현 및 스킬트리 구현
- (현범) 인벤토리 구현


## 5주차
**1. 이번 주에 한 것**

- 게임 컨셉 및 적용 기술, 진행 예상도 구상

**2. 스크린샷**
![Image](https://github.com/simeddk/HellWorld/assets/41534351/964a9324-50e6-4e5f-b5e4-c8801eeda737)

**3. 고찰 및 다음 주 할 것**
- Time Dilation, Inventory 구현 완성


## 6주차
**1. 이번주에 한 것**
- 상태이상에 걸렸을 때 플레이어의 속도 저하, 또는 플레이어의 가속을 위한 TimeDilation ActorComponent 생성
- MultiPlay Widget 생성
- 인벤토리 UI 구현
- 월드 상에 있는 아이템 획득 시 인벤토리로 이동

**2. 스크린샷**


![Image](https://github.com/simeddk/HellWorld/assets/41534351/341b10aa-11a5-4189-9c4b-7b30f2c69f36)
<MultiPlay Widget 생성>


![Image](https://github.com/simeddk/HellWorld/assets/41534351/29fc0530-d2f6-4df0-ab3b-20aeea59df64)
<인벤토리 UI 구현>


**3. 고찰 및 다음주 할 것**
- 가능하다면.. 인벤토리 및 멀티플레이 마무리(아마 힘들거 같지만 최선을 다해보겠습니다..)


## 7, 8주차
**1. 이번주에 한 것**
- TimeDilationComponent : GlobalTimeDilation -> CustomTimeDilation으로 변경
- OSS Create/Destroy Session 구현
- 인벤토리 전면 수정

1. 상호작용 가능한 오브젝트
-> 상호작용을 위한 InteractComponent 생성
InteractComponent를 가진 오브젝트가 무엇인지 그리고 player, Item과의 상호작용 상태를 확인하기위한 Component
-> PlayerCameraLineTrace
PlayerCamera의 시작되는 LineTrace로 InteractComponent를 가진 오브젝트를 찾는다.
-> Interact할 물체 정보창Widget 생성
LineTrace에서 찾은 오브젝트가 InteractComponent를 가졌다면 해당 오브젝트의 정보창, 기능, 갯수 등을 표기한 정보창 spawn

2. InventoryComponent 생성
-> Item, FoodItem(Item을 상속받은) C++ 클래스 생성
  게임중 이름, 설명, 무게, 중복소유가능여부, 총 소유갯수 포함
-> Interact하여 Item일경우 Data를 가져와 InventoryWidget으로 data를 전달(미구현)


**2. 스크린샷**

![Image](https://github.com/simeddk/HellWorld/assets/41534351/fd1fb4b9-9984-487a-b539-305043c87d36)


<인벤토리 UI 수정>



![Image](https://github.com/simeddk/HellWorld/assets/41534351/2cbf93e9-5151-4dc7-873c-4ffbc79f8517)


<Object와 Interact>


**3. 고찰 및 다음주 할 것**
- OSS 마무리
- Item Mesh 및 Inventory Thumbnail 추가


## 9주차
**1. 이번주에 한 것**

1. OSS
- OSS 완성할 수 있었으나.. 작업물을 날려버려서 다시 Create/DestroySession 구현
- FindSession UI 다시 제작 중

2. Inventory
https://youtu.be/JiAZ2-J3T0A
- Gun(Item Mesh) 추가 (하단 스크린샷 사진 첨부)
- Drop, use System구현
-> Drop : Item을 버리는 함수.
Inventory Widget의 Item Slot 밖으로
Item을 Click -> Drag -> Release하면 Item이 World에 버려짐(World에 Spawn됨)

-> Use : 아이템을 장착하는 것까지는 구현하지 못하였고, Use함수를 호출하면 간단하게 Print함수만 호출되게 한 상태

**2. 스크린샷**

![Image](https://github.com/simeddk/HellWorld/assets/41534351/09fa7b11-6768-4668-a317-252874dc4e69)
<Gun(Item Mesh)>


**3. 고찰 및 다음주 할 것**
- 이번 주 중에 OSS 마무리
- 구해놓은 Asset 적용
- Item 구현 및 Use 함수 완성


## 10주차
**1. 이번주에 한 것**

1. OSS
- FindSession까지 완료.

2. Inventory
https://youtu.be/5jAUMOePUg0
- Drop함수 버그 수정
 -> 인벤토리에 있는 아이템을 버리면 랜덤한 시간동안 기다려야 아이템이 완전히 버려지는 버그 수정

**2. 고찰 및 다음주 할 것**
- JoinSession, GameMode -> postLogin, Logout, GameStart 구현
- Player mode(unarmed, action 등) 구현
- Item 구현 및 Use 함수 완성


## 11주차
**1. 이번주에 한 것**

(1) OSS
- JoinSession까지 완료
- GameMode 및 Start Session은 Player와 Enemy 구현 후 진행할 예정


(2) Inventory
- OSS를 통해 Client Travel로 접속한 Player 버그 2가지 발견
 -> Interaction이 안되는 버그
 -> Parkour(벽을 타고 올라가지 못함) 버그


(3) Map Asset 최종 결정
- 맵 2개 사용(동일한 배경, 낮과 밤의 변경을 통한 분위기 고조 연출 예정)



![Image](https://github.com/simeddk/HellWorld/assets/41534351/6719848c-c4f5-4d7b-93a2-8092f831921f)




![Image](https://github.com/simeddk/HellWorld/assets/41534351/3a494adc-eb14-4bff-9c12-05403fee42a6)



(4) 지금까지 구현한 부분 문서로 정리



![Image](https://github.com/simeddk/HellWorld/assets/41534351/6046cab9-73ab-4634-86e0-fff8dbc0c2bc)




**2. 고찰 및 다음주 할 것**
- Player 구현
- Inventory 버그 개선
- Item 구현 및 Use 함수 완성


## 12주차
1. 이번주에 한 것
- 컴포넌트 생성 (Status, State, Montages)
(1) Status -> 캐릭터 이동/능력 구현 (체력은 추후 구현 예정)
(2) State -> 캐릭터 상태 Enum으로 선언 및 상태변경 Getter/Setter 함수 선언
(Idle, Jump, Warp, Equip, Action, Hitted, Dead, Max)
(3) Montages -> Montage 구조체 선언 및 DataTable에 바인딩(성공)

2. 스크린샷


![Image](https://github.com/simeddk/HellWorld/assets/41534351/dc651c16-e9a6-4c6a-9508-9f92b9baf3d4)




3. 고찰 및 다음주 할 것
- Player ActionComponent 생성 및 DataAssets 응용
- Player 일단락 낸 후, Enemy 제작
- Inventory 버그 해결 후 Item생성 시작


## 13주차
1. 이번주 프로젝트 진행 상황
* Host, Client server간 버그 fix
* 각 서버 inventory 기능 정상작동
  
2. 사진첨부   
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/54293456-3249-4593-b64c-22fe8c362959)
   
3. 고찰 및 다음주 할 것
* Item.Class의 use함수 내용 작성
* Item Datatable 생성
* parkour Montage 적용 및 Test
  
## 14주차
1. 이번주 프로젝트 진행 상황
* item Asset 가져오기, 월드상에 스폰
* item use함수(inventory에서 아이템 thumbnail 더블 클릭시 실행 하는 함수) 실행시 각    weapon class의 attachment 실행
* 점프 montage를 사용하는 방식에서 animgrap(WBP)로 바꾸며 더 자연스러워짐

2. 사진첨부
   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/38c305e8-fffb-4808-8572-8ed4317e6b0f)

3. 고찰 및 다음주에 할 것
* ParkourSystem 멀티 플레이화 및 현제 플레이어 스켈레톤 메시에 맞는 몽타주 파밍 및 적용
* 아이템 데이어테이블 작성
  
## 15주차
1. 이번주 프로젝트 진행 상황
-Item Attachment
*short sword 크기 조절

* 무기 클레스 CWeapon_Sword, CWeapon_Sniper를 따로 만들어서 attachment 함수 생성 (각 무기 클라스는 스켈레탈 메시를 가지고있는 actor이다.)

* Player.cpp use함수 에서 바로 호출하는 방식으로 바꿈

* if조건으로 아이템 등급으로 사용하기위해 만들었던 EItemRarity를 사용하여 각 무기를 나누고 pickupBase아이템 설정에서 등급을 수동으로 주어 각 아이템의 등급을 부여

2. 사진첨부
* short sword 크기 조절
  ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/fd158a84-d5f9-418f-a75d-be837d312f26)

* Player.cpp use함수 에서 바로 호출하는 방식으로 바꿈
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/1ffc203b-1cd2-4ff3-b901-171e18866bfa)

* 등급에 따른 if문 Attachment
![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/e909fa78-005c-40bb-9d90-f963cba92241)

3. 고찰 및 다음주에 할 것
* ParkourSystem 멀티 플레이화 및 현제 플레이어 스켈레톤 메시에 맞는 몽타주 파밍 및 적용
* player state 작업 시작
  
## 16주차
1. 이번주에 한 것
- CWeapon_Sniper, CWeapon_Sword를 CWeapon의 자식으로 상속시킴
- ActionComponent 정의 중 
- Player에 관한 구성요소들을 DataAsset(ActionData)에 정의할 예정
 -> ActionData 구성 요소
  => (CWeapon Component) Player weapon 제작 완료
  => (CEquipment Component) Equip하는 몽타주 제작 중
  => (CDoAction Component) Player가 장착한 Weapon에 따른 Action 제작 예정

2. 스크린샷
- 좀더 완성된 후인 다음 주에 스크린 샷 첨부하겠습니다.

3. 고찰 및 다음주 할 것
- Player 일단락짓기
- 각종 Animation 및 Enemy Asset 리타깃


## 17주차
<h3>**1. 이번주에 한 것**</h3>

(유태)
- Player의 Weapon, Equipment, DoAction을 관리할 DataAsset(CActionData) 구성
 -> (Weapon) 무기 장착 및 해제 시 Attach되는 Socket변경
 -> (Equipment) 무기 장착 시 몽타주 재생, Notify를 활용한 BlendSpace상태 유지 및 해제
 -> (DoAction) 추후 작업 예정

-  아직 해결하지 못한 것
 -> Inventory에서 무기를 장착해야 무기 장착 몽타주를 재생할 수 있어야 하지만, 지금은 무기를 장착하지 않아도 몽타주가 재생될 때 무기가 Spawn됨.
https://www.youtube.com/watch?v=AutQ0_UdCCU

(현범)
- 현재 SkeletalMesh에 맞게 Montage들을 리타겟 작업함
- ParkourSystem 멀티플레이 환경에 맞게 C++코드 수정
- 낮은 지형을 미끄러지면서 이동하는 Vault가 현제 캐릭터의 skeletalmesh에 맞는 montage가 없어서 제거함
https://youtu.be/bDcn5IZL_90



<h3>**2. 스크린샷**</h3>

![Image](https://github.com/simeddk/HellWorld/assets/41534351/3232e46d-6a88-4a61-b70d-48b2daf0140f)

<CWeapon_Sword의 BP>



![Image](https://github.com/simeddk/HellWorld/assets/41534351/ed14d8d7-4c78-4245-a98f-db604a12d78b)

<ParkourSystem 코드 수정>



<h3>**3. 고찰 및 다음주 할 것**</h3>

- Player DoAction 정의
- DataAsset에 아직 붙이지 않은 Weapon, Equipment Asset 장착
- 무기를 장착해야 몽타주가 실행되도록 Fix
- Enemy 생성 및 BehaviorTree제작
- Enemy montage작업 및 AI생성


## 18주차
<h3>**1. 이번주에 한 것**</h3>

1. Cweapon이 Holster Socket에 붙어있지 않을 때 무기를 사용할 수 없도록 변경
2. Sniper DoAction Montage 제작
3. Dissolve Material 구현 및 적용
https://youtu.be/yTe7Dtlw55s

<h3>**2. 고찰 및 다음주 할 것**</h3>

<다음 주까지 프로젝트 마감 후 문서작업 예정>
- Sniper DoAction 시 Bullet생성
- Sniper 장착 시 Aim Offset 적용
- Character HP 및 Collision 생성
- Start Session 시 Map 변경 예정
- Enemy montage작업 및 AI생성
- Enemy 생성 및 BehaviorTree제작
