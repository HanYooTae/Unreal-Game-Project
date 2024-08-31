## 장착 아이템 구성

#### 아이템의 장착은 DataAsset으로 관리하고 있으며, 해당 DataAsset은 아이템의 정보, 장착, 공격 등의 정보를 관리한다.

#### 아이템 DataAsset은 Player와 Enemy가 공용으로 사용한다.

![image](https://github.com/user-attachments/assets/391c5c47-20dc-4f13-a25d-f46227955749)
```
Weapon
 - 무기의 SkeletalMesh
 - 장착되었을 때 Player or Enemy에게 붙을 Socket 정보
```

![image](https://github.com/user-attachments/assets/69f22324-b07b-4d6a-9f37-af53427499e4)
```
Equipment
 - Player가 무기를 장착할 때 재생되는 몽타주
 - 몽타주 재생 속도
 - 움직일 수 있는지, 뒤돌아 볼 수 있는지 여부
```

![image](https://github.com/user-attachments/assets/5a48a79c-a0fc-4918-b437-ab8e1ab61a86)
```
DoActions
 - Player가 무기를 장착한 후에 공격했을 때 재생되는 몽타주
 - 몽타주 재생 속도
 - 무기의 Damage
 - Combo 여부
 - 움직일 수 있는지, 뒤돌아 볼 수 있는지 여부
 - 무기가 총기류일 경우, Spawn되는 총알
```
