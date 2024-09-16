## 프로젝트 소개

### Steam OSS와 RPC를 활용한 2인 멀티플레이 게임

- 2인 팀 포트폴리오 / Unreal Engine 4.27
- 목차 옆에 팀원 이름이 적혀있다면, 해당 기능은 이름이 적혀있는 팀원이 전부 구현한 것입니다.
- 목차에서 팀원별 역할이 기재되지 않은 부분은 상세보기를 통해 팀원 별 상세한 역할을 확인하실 수 있습니다.

## 프로젝트 소개 영상

[![image](https://github.com/HanYooTae/Unreal-Game-Project1/assets/41534351/219315b8-22ca-4c86-8ea6-e220abdc1c53)](https://youtu.be/LedMGxR1QEk)


## 개발 기간
- 2023/07/30 ~ 2023/12/17


## 프로젝트 목차

### Online SubSystem (한유태)
> + #### 위젯 구성
>   OSS 위젯은 Widget Switcher 기능을 이용하여 하나의 위젯으로 구현
>   + [상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem_Widget.md)
> + #### OSS 구성
>   Create, Destroy, Find, Join, Start Session 기능 활용
>   + [상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/OnlineSubSystem/OnlineSubSystem.md)


### 캐릭터

> + #### 사용자 정의 컴포넌트
>   사용자 정의 컴포넌트는 플레이어와 몬스터를 구분하지 않고 사용하는 컴포넌트와, 구분하는 단일 사용 컴포넌트가 존재한다.
>   + [상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Characters/Components/Components.md)
>
> + #### 플레이어 (한유태)
>   사용자 정의 컴포넌트 기능을 제외한 플레이어의 기능은 Minimap과 HUD, 무기 변경 위젯이 있다.
>   + [미니맵 상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/MiniMap/Minimap.md)
>   + [HUD 상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Utilities/HUD.md)
>   + [무기 변경 위젯 상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/%EB%AC%B4%EA%B8%B0%20%EB%B3%80%EA%B2%BD%20%EC%8B%9C%EC%8A%A4%ED%85%9C/%EB%AC%B4%EA%B8%B0%20%EB%B3%80%EA%B2%BD%20%EC%8B%9C%EC%8A%A4%ED%85%9C.md)
>
> + #### 몬스터 (김현범)
>   이동, 감지, 공격, 피격, 죽음의 기능을 가진 AI Controller를 소유한 개체이다.
>    + [몬스터 구성](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Characters/Enemy/Enemy.md)


### 인벤토리 (김현범)
> + #### 인벤토리
>   아이템의 갯수, 무게 Text 를 표기, 현 아이템의 상태를 체크하는 함수, 새로고침, Inventory에 아이템 추가/제거 기능을 가진 Actor Component이다.
>   + [인벤토리 구성](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Inventory/inventory.md)
> + #### 상호작용
>   linetrace로 작동하며 감지시작(begin focus), 감지종료(end focus), 사용시작(begin interact), 사용종료(end interact), 사용(interact) 5개의 기능을 주로 하며 
  linetrace의 result값의 감지의 유/무에 따라 WB_InteractionCard인 위젯을 화면에 올려주고 내려줌.
>   + [상호작용 시스템](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Inventory/Interact.md)


### 아이템
> 아이템의 종류는 Sword와 Sniper 총 2가지가 있다.
> 월드 상에 스폰되어있는 필드 아이템과 상호작용을 통해 장착하는 장착 아이템으로 구성되어있다.
>
> + #### 필드 아이템 구성 (김현범)
>   begin play후 월드에 지정된 장소에 생성되며 상호 작용후 플레이어의 인벤토리에 데이터를 저장할 수 있는 아이템 저장후 인벤토리에서 더블클릭후 장착아이템으로 사용됨
>   + [상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Items/Items.md)
>     + [검 아이템](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Items/Sword.md)
>     + [총 아이템](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/Items/Sniper.md)
> + #### 장착 아이템 구성 (한유태)
>   장착 아이템은 DataAsset으로 관리하고 있으며, 해당 DataAsset은 아이템의 정보, 장착, 공격 등의 정보를 관리한다.
>   + [상세보기](https://github.com/HanYooTae/Unreal-Game-Project1/blob/main/%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8%20%EA%B0%9C%EC%9A%94/DataAssets/DataAssets.md)
