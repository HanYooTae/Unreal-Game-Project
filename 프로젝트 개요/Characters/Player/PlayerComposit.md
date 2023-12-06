# Player 애니메이션
Player는 무기를 착용하지 않은 기본 Unarmed와 여러 무기를 착용했을 때의 기본 모션이 나뉘어져 있음

각 기본 모션은 BlendSpace로 구성하였으며, 방향마다 다르게 모션을 취하게 하기 위해 BlendSpace2D를 사용하였음

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/71be9483-32e1-4511-813b-eb26a50d264f)

AnimInstance에서 Tick으로 현재 캐릭터의 WeaponType을 받아서 현재 무기에 따라서 기본 모션을 바꿀 수 있게 설정

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/437f5280-fe5f-49aa-8eb2-cbe2ce0593c7)


여러 몽타주들을 사용할때에는 상반신만 움직일지 혹은 몸 전체가 움직일지에 따라 다르게 블렌딩 작업을 진행함

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/81787397-a770-4f24-9877-da1b9fc5bfd5)
