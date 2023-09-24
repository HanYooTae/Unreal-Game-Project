Drop Item Bug

아이템을 버릴때 인벤토리에서 thumbnail이 늦게 지워지는 bug가 있었다.

1. 해결방법

    inventory를 열고 닫았을때 수동으로 최신화가 되는 구조였다.
    RemoveItem이라는 아이템을 제거해주는 함수에서 바로 최신화하기 위해서는 
    ClientRefreshInventory라는 새로만든 최신화를 해주는 함수가 필요했다.

2. fix한 코드는 아래와 같다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/60e28376-aaf0-4cc4-a337-af0536bf3b2f)


참고영상
bug fix전 : https://youtu.be/HZYjlxezU5Y
bug fix후 : https://youtu.be/dhlBdeyTq6c


