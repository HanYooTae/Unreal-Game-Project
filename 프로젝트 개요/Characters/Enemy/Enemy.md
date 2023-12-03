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
  *
## PatrolPath, PatrolComponent
- CPatrolComponent
- CPatrolPath
## BehaviorTree
- CBTService_Enemy
- CBTTaskNode_Action
- CBTTaskNode_MoveSpeed
- CBTTaskNode_Patrol
- CEnvQueryContext_Player
- BehaviorTree BluePrint
