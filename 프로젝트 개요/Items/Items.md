#Item

## Item
  -GetLifetimeReplicatedProps()
  
      액터 채널의 수명 동안 복제되는 속성을 반환하는 함수.

    * 사진 자료

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/4cff6269-1635-41b6-be09-c4ed3c77466a)

  -IsSupportedForNetworking()
  
    네트워크를 통해 개체를 참조할 수 있음을 의미하는 함수.

    * 사진 자료

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/30f470cb-9b9c-44d7-a9f2-6ba6fd802fee)

  - PostEditChangeProperty()
    
    언리얼 에디터의 런타임 변경사항은 반영되지 않고, 에디터에서 타겟 오브젝트의 값이 변경되면 알려주는데 이때 필요한 함수. (에디터 전용 #ifdef 안에 있는데 실행파일 크기를 불필요하게 늘릴수 있는 여타 코드를 제거하기 위함)

    * 사진 자료

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/3b1daa23-5598-4dbc-8784-fa955e7c3d96)

  - SetQuantity()

    갯수를 표기할때 1과 최댓값 사이에 표기가 되어야하며 아이템을 복제용으로 설정해주는 함수

    * 사진 자료
   
      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/730dbc5d-ee19-4bee-87f2-aa25cddbac37)

  - MarkDirtyForReplication()

    인벤토리 항목을 효율적으로 복제하는 데 사용할 변수 RepKey를 증가해주며 복제할 어레이 표시도 같이 실행하는 함(UCInventoryComponent의 복제를 위한 변수 ReplicatedItemsKey 증가)

    * 사진 자료

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/11b6db9c-c018-4420-9e4e-72f94d75a98b)

  - Use()
    
    Player가 아이템을 인벤토리에서 사용하면 갯수를 1개씩 내림

    * 사진 자료

      ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/afff0ecb-9782-4e26-b95d-89bbe7b12660)

  - UCFoodItem, UCWeaponsItem

    UCItem을 상속받은 class. UCFoodItem은 소비 아이템이며 UCWeaponsItem은 장착 아이템으로 분류

    
## Pickup
  Item을 World상 배치하며 배치된 아이템의 정보를 가진Actor class

  * 사진 자료

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/39682899-ce55-41cb-993f-c2f9a9b4420c)

  - InitializePickup
    
    아이템의 갯수를 저장한 상태로 필드에 스폰

  * 사진 자료

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/45e21351-4f24-4089-8072-55db292ef9f9)


  - OnTakePickup()

    Pending Kill이 필요하다고 100% 확신할 수는 없지만 다른 플레이어가 이미 가져가려고 시도한 픽업을 플레이어가 가져가는 것을 방지 (IsPendingKillPending() : 액터가 소멸 프로세스를 시작했다면 참을 반환)
    
  * 사진 자료

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/11c06f53-79ea-417b-a873-8265174ac038)


     
