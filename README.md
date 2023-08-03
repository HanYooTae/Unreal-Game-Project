# Unreal-Game-Project1

Parkour System 설명

<헤더>
함수
  	void Vault();		// 플레이어 V키를 누르면 실행되는 함수
	void JumpAndUp();	// 점프를 확인하는 함수
	void Jump();		// 점프를 했을때 실행하는 함수
	void Up();			// 점프를 하지않았을때 실행하는 함수

	void NextMontageYorN(); // Climb Montage다음에 나올 JumpingDownFromWall을 실행 할지에대한 if문
	void LastCollision(); // Montage_Play 함수에서 불러낼 마지막 콜리전 셋팅 함수

 변수
 	FVector WallLocation;	// 위치저장 변수
	FVector WallNormal;		// normal vector 저장변수 <- 많이 사용하지 않음 (필요성을 느끼지못함)
	FVector WallHeight;		// 높이 저장 변수
	FVector WallHeight2;	// 높이 저장 변수2

	bool Canclimb;			// 올라갈수 있는지에대한 bool변수
	bool ShouldPlayerClimb;	// 점프를 통한 parkour 실행 bool변수
	bool IsWallThick;		// 물체의 두께를 학인하고 올라갈지 넘어갈지에 대한 bool번수
	bool IsClimbing;		// 현제 parkour를 하고 있는가에 대한 bool변수

 <CPP>
 Trace종류
 1. player 전방 물체 인식trace
 2. 1번 Trace에 걸린 물체의 높이를 구하는 Trace
 3. 2번 Trace와 플레이거앞에 있는 Trace이며 물체의 두께를 츧정하는 Trace
 4. 점프를 통해 올라갈수 있는지여부를 판단하는 trace
 5. 점프 parkour를 통해 넘어갈려할때 player위쪽 장애물의 유무판단(따로저장값없음 현제 필요없는 Trace 추후 필요하다면 변수를 추가하여 사용가능)

 주요 함수
 1. LineTrace
 UKismetSystemLibrary::LineTraceSingleForObjects
 (
   const UObject* WorldContextObject,
   const FVector Start, 
   const FVector End, 
   const TArray<TEnumAsByte<EObjectTypeQuery> > & ObjectTypes, 
   bool bTraceComplex, 
   const TArray<AActor*>& ActorsToIgnore, 
   EDrawDebugTrace::Type DrawDebugType, 
   FHitResult& OutHit, 
   bool bIgnoreSelf, 
   FLinearColor TraceColor, 
   FLinearColor TraceHitColor, 
   float DrawTime
 );
ex)
bool Result = UKismetSystemLibrary::LineTraceSingleForObjects 
		(
			GetWorld(),
			Start,
			End,
			ObjectTypes,					// 비워둘수 없어서 기본값 셋팅
			true,
			ignoreActor,					// 비워둘수 없어서 기본값 셋팅
			EDrawDebugTrace::ForDuration,
			hitResult,
			true,
			TraceColor.Red,
			TraceHitColor.Green,
			5.0f
		);
if (Result == true)
		{
        OutPut 저장
        ex)
        WallLocation = hitResult.Location;
    }

2. Collision and MovementMode
Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::type);
Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::type);
ex)
Owner->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
Owner->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);

3. Montage_Play (UCAnimInstance)
UAnimMontage형 변수에 ConstructorHelpers::FObjectFinder를 사용하여 AnimMontage를 가져와 Montage_Play함수를 사용해서 재생
UAnimInstance::Montage_Play(UAnimMontage* MontageToPlay, float InPlayRate, EMontagePlayReturnType ReturnValueType, float InTimeToStartMontageAt, bool bStopAllMontages)
ex)
void UCAnimInstance::PlayClimbMontage()
{
	if (!Montage_IsPlaying(ClimbMontage)) // 현제 플레이중인가에 대한 검사
		Montage_Play(ClimbMontage, 1.0f);	
}
함수 싱행 : AnimInstance->PlayClimbMontage();

4. Delay를 대신한 함수 GetWorld()->GetTimerManager().SetTimer()
Delay를 대신하기위한 함수
사용한 함수 코드
1. GetWorld()->GetTimerManager().SetTimer(timerHandle, this, &UCParkourSystem::NextMontageYorN, 1.13f);
 - 1.13초후에 &UCParkourSystem::NextMontageYorN 함수를 실행  
2. GetWorld()->GetTimerManager().SetTimer(timerHandle, 1.0f, false);
 - 1초의 Delay Loop = false 
