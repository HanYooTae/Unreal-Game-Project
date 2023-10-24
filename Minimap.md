## Main Widget 구현 (한유태)

1. Create Main Widget
   - (코드의 재사용성 활용) 앞으로 만들어질 모든 widget들을 Main Widget에 붙일 예정.
   - CPlayer.h
     
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/8c2e560f-4f17-4a02-a95e-a308acda6261)

   - CPlayer.cpp (constructor)
  
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/ecaec390-d942-4cff-aae3-ee80e8fb89b1)

   - WB_MainWidget
     
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/af185237-f1ef-42dd-b028-31ee29c957c2)

     

## Minimap 구현

1. Create Minimap
   - Player에 Z축 방향으로 SpringArm을 붙인 후, USceneCaptureComponent2D로 랜더링하여 Top View 시점으로 랜더링하였음
   - PaperSprite를 추가하여 Sprite Image로 화살표를 사용하여, Player가 움직이는 방향이 어딘지 확인할 수 있게 구현하였음 
   - CPlayer.h
  
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/41aef907-2fd4-4d6e-9aee-efea4efb7b8f)

   - CPlayer.cpp (constructor)
  
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/edc21b7d-8d6e-41fd-be1e-a92e0a4294c4)

   - WB_Minimap
  
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/73cc9302-4f62-4772-a78c-4b63f000bf30)



2. Attach minimap to main widget
   

     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/8a668b71-88f7-44e3-a041-59ed21fdb327)


3. PaperSprite
   - C++로 구현하려고 하였지만, 헤더파일을 찾지 못하여 어쩔 수 없이 Blueprint로 구현...
   - Minimap에서 Player의 방향을 표시하기 위하여 사용
   - Mesh의 자식으로 PaperSprite를 붙여주었으며 Sprite image를 붙인 후, Owner no see를 통하여 Player는 Sprite image를 볼 수 없게 구현하였음
  
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/c5afcc3e-95ee-44ee-8486-c910e91bc7ef)
     ![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/56104fa9-930d-4777-b045-7465a0922e32)
)
