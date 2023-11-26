## Animation
Skeletal에 맞지 않아 정상 작동 되지않는 버그가 있었다.

1. 해결방법
mixamo root본의 이름이 unreal root본의 이름과 다르다는걸 알았다. blender를 사용하여 hips라는 mixamo root본 이름을 unreal root본 이르으로 바꾸는 작업을 했다.

2. fix한 animation은 아래와 같다.

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/53bc5058-ee7c-4709-95e3-106c37818743)

* vault 와 getiing up animation은 mixamo에서 구할 수 없었으며 또한 캐릭터에 자체 점프가 있기 때문에 제외하기로 결정했다.

## RPC
RPC환경에 server와 clinet가 서로 안보이는 버그가 있었다.

1. 해결방법
server로 한번 정보를 올려주는 함수 Parkour를 만들고 client에게 server에서 나온 정보를 서로 공유하기 위한 UFUNCTION키워드 server와 netmulticast를 사용하였다.

fix한 코드

![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/123162344/b377775c-f8ce-4f14-ba62-8a489246256f)


### Parkour관련 영상

https://youtu.be/bDcn5IZL_90
 
