## Drop Item Bug

아이템을 버릴때 인벤토리에서 thumbnail이 늦게 지워지는 bug가 있었다.

1. 해결방법

    inventory를 열고 닫았을때 수동으로 최신화가 되는 구조였다.
    RemoveItem이라는 아이템을 제거해주는 함수에서 바로 최신화하기 위해서는 
    ClientRefreshInventory라는 새로만든 최신화를 해주는 함수가 필요했다.

2. fix한 코드는 아래와 같다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/60e28376-aaf0-4cc4-a337-af0536bf3b2f)


<참고영상>

- bug fix전 : https://youtu.be/HZYjlxezU5Y

- bug fix후 : https://youtu.be/dhlBdeyTq6c

## Interact Bug 
아이템과 플레이어와의 상호작용중 아이템 정보창인 interactCard가 server와 client간의 연결에서 버그가있었다.

1. 해결방안
- CPlayer에서 상호작용의 가능의 여부를 판단하는 두함수가 있는데 그함수들을 호출하는 라인트레이스 함수에 UFUNCTION(Reliable, Server)를 추가하고 호출받는 두함수에 UFUNCTION(NetMulticast, Reliable) 를 추가해 주었다. 이는 두함수가 서버를 한번 거쳐서 나와야 한다고 판단이 되었기 때문이다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/36673683-6a7f-461b-9c39-588ca582e95a)

2. 아쉬운 부분
- 처음 원했던 완성본은 server와 client가 서로 정보창을 공유하지 않고 개인적으로 볼 수 있게 해주는것이 목적이었다. 하지만 이럴 경우 아이템이 상호작용중 먹어지거나 기능이 실행에 있어서 큰 문제가 있었다. 때문에 서로 정보를 공유하기로 결정했다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/2ab682b3-42cb-47dd-860a-403ba275db81)

