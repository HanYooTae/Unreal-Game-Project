# Item
#### 기능 
   - 액터 채널의 수명 동안 복제되는 속성을 반환.
   - 갯수를 표기할때 1과 최댓값 사이에 표기가 되어야하며 아이템을 복제용으로 설정
   - 인벤토리 항목을 효율적으로 복제하는 데 사용할 변수 RepKey를 증가해주며 복제할 어레이 표시도 같이 실행(UCInventoryComponent의 복제를 위한 변수 ReplicatedItemsKey 증가)
   - Player가 아이템을 인벤토리에서 사용하면 갯수를 1개씩 내림
   - Item종류 로는 UCFoodItem, UCWeaponsItem이 있다
      * UCItem을 상속받은 class. UCFoodItem은 소비 아이템이며 UCWeaponsItem은 장착 아이템으로 분류

   ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/97daaef4-575c-4b91-9c18-6892c26d5f22)

### Sniper

#### 소개
  - Collision이 없으며 소켓장착으로만 사용하는 class
  - 원거리 무기이며 줌기능, 발사기능이 있다.

#### 사진 자료


![image](https://github.com/user-attachments/assets/8010b3b6-224f-45aa-88c1-bee9211eab63)

### Sword

#### 소개
  - Collision이 존재하며 소켓장착하여 직접 몽타주를 재생해 타격할수 있는 class
  - combo attack기능이 있다.

#### 사진 자료


![image](https://github.com/user-attachments/assets/187f3458-337f-43aa-9392-60ba633f2a29)
