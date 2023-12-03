# Enemy

##  Actor, AIController

- Mesh, Material
  
  * Goblin형태의 mesh사용, Dissolve기능이 들어가있는 Material 사용
    
  * 사진 자료(Material)
    
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/1f5483b8-54c6-4da3-b8ec-43a394b3d5d2)

  * 사진 자료(Mesh)
    
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/8de18e9b-b437-47f2-ba52-2cee88c70ed9)

- Animation
  
  * idle, warlk, run, attack의 animation으로 구성 그중 idle, warlk, run는 Blendspaces로 만들어 애니메이션 블루프린트로 만듬
    
  * 사진 자료
    
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/81f731ac-9151-4498-93ef-9fa978bcd799)

- CEnemy
  
  * 생성자에서는 1. actor component 2. mesh 셋팅 3. movementcomponent셋팅
    
  *사진 자료

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/b9f2402f-d982-4280-a9d2-b0cf49e17120)

- CEnemy_AI

  * PatrolPath를 사용하기위한 Patrolcomponent셋팅, Behavior Tree에서 playerkey를 가져오기위한 TeamID셋팅
    
  * 사진 자료(Patrolcomponent셋팅)
    
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/a1101a97-c6e2-4971-b1cc-ea13b4195152)

  * 사진 자료(BehaviorTree)
    
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/19907580-f7f6-4aa4-8cf3-def887df4056)

- CAIController
  
  * Perception
    
  * 사진 자료(기본 셋팅)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/6ae09d33-3ad2-443d-a899-79f451b7b542)

  * 사진 자료(Possess)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/56bff5ed-29bb-49a0-94fb-b292e95367c9)

  * 사진 자료(Perception Updated)
 
    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/aa623c7b-0473-491b-9a10-23d3503f95aa)

## PatrolPath, PatrolComponent
- CPatrolComponent
  PatrolPath의 SplinePoint위치, 이동할 위치를 뜻하는 Index값 설정

  * 사진 자료(Index값 설정)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/59780a23-fc13-41ba-b46d-e443b37266a9)

  * 사진 자료(Index를 사용한MoveToLocation)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/8c1339fc-7fda-4cd8-8ed0-249467b1e8bb)

- CPatrolPath
  이동 경로 역할의 Patrolpath셋팅

  * 사진자료(기본셋팅)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/09e57b39-49fc-4deb-957b-44418615bc92)

## BehaviorTree
- CBTService_Enemy
  ModeChange, Playerkey가져오기, 취할 행동들을 세팅해주는 script

  * 사진 자료(PlayerKey)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/21d46db6-1022-424a-a234-70af3e1dc771)

  * 사진 자료(ModeChange)

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/d861375e-48ba-416b-bd4f-d576c52f7331)

- CBTTaskNode
  
  Action, MoveSpeed, Patrol의 기능을 가지며 Action은 UCActionComponent::DoAction(), MoveSpeed는 UCStatusComponent::ChangeMoveSpeed(), Patrol은 UCPatrolComponent::GetMoveToLocation()을 각각 실행한다.
  
- CEnvQueryContext_Player
  PlayerKey를 가져오는 것을 목적으로 하는 script

  * 사진 자료

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/50f9d481-1e36-44ac-92c1-beca73f71d30)

- BehaviorTree BluePrint

  * 사진 자료

    ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/d1308ae5-a94d-44ad-b7f6-ebda87c0bbc1)
