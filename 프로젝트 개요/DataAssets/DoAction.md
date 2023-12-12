# DoAction

DoAction의 경우, TArray(Vector)로 구현하여 콤보가 가능한 무기로 연속 공격 시 ComboCount를 증가시켜 콤보공격이 가능토록 구성

Character가 장착한 무기에 알맞는 공격몽타주를 실행시키는 구조체

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/a7d6ca9d-eb07-40c1-a108-639ffe0981da)

+ Power : 무기의 공격력
+ Hit Stop : Character를 공격하면 설정한 수치만큼 게임 플레이 속도가 변경됨
+ Effect : Character 공격 시 Particle 재생
+ Effect Transform : Particle의 생성 위치
+ Shake Class : Character를 공격하면 화면이 흔들리도록 Camera Shake 적용
+ Projectile Class : 원거리 무기(총)의 경우, [총알](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/DataAssets/Bullet.md)이 Spawn되게 함
+ Anim Montage : 무기장착 몽타주 실행
+ Play Rate : 몽타주의 실행 속
+ Start Section : 몽타주의 실행 섹션
+ Can Move : 무기를 장착하는 상태(Equip)동안 이동 가능 여부
+ Pawn Control : 무기를 장착하는 상태(Equip)동안 정면만 바라보게 할 것인지

* 참고 영상

    [![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/99e5aa0a-1ea2-45ed-b9a3-dc716f658022)
](https://youtu.be/A5RssflIlDU)
