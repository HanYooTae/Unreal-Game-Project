#include "CharacterComponents/CMontagesComponent.h"
#include "GameFramework/Character.h"
#include "Global.h"

UCMontagesComponent::UCMontagesComponent()
{
}


void UCMontagesComponent::BeginPlay()
{
	Super::BeginPlay();

	if (DataTable == nullptr)
		CLog::Log("DataTable is not set");

	TArray<FMontageData*> datas;
	DataTable->GetAllRows<FMontageData>("", datas);

	for (int8 i = 0; i < (int8)EStateType::Max; i++)
	{
		for (const auto& data : datas)
		{
			if ((EStateType)i == data->Type)
			{
				Datas[i] = data;
				break;
			}
		}
	}
}

void UCMontagesComponent::PlayHitted_Implementation()
{
	PlayMontage(EStateType::Hitted);
}

void UCMontagesComponent::PlayDead_Implementation()
{
	PlayMontage(EStateType::Dead);
}

void UCMontagesComponent::PlayMontage_Implementation(EStateType InStateType)
{
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner());
	CheckNull(ownerCharacter);

	const FMontageData* data = Datas[(int32)InStateType];

	if (!!data && !!data->AnimMontage)
		ownerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayRate, data->StartSection);
}
