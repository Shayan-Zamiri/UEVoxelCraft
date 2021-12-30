#include "VCBaseBlock.h"

#include "VCGameModeBase.h"
#include "VCProceduralGenerator.h"
#include "Components/BoxComponent.h"

// STATICS

float AVCBaseBlock::BlockSize = 100.0f;

// CTOR/DTOR & VIRTUAL FUNCTIONS

AVCBaseBlock::AVCBaseBlock() : bIsBreakable{true}
{
	PrimaryActorTick.bCanEverTick = false;

	RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
#if WITH_EDITOR
	RootSceneComp->bVisualizeComponent = true;
#endif
	RootComponent = RootSceneComp;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionProfileName("BlockAll");
	BoxComp->SetBoxExtent(FVector{BlockSize / 2, BlockSize / 2, BlockSize / 2});
	BoxComp->SetRelativeLocation(FVector{0.0f, 0.0f, /*because of SM_Cube's pivot*/ BlockSize / 2});
	BoxComp->SetupAttachment(RootSceneComp);
}

void AVCBaseBlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GridSnapBlock();
}

// FUNCTIONS

FVector AVCBaseBlock::GetCenterOfCube() const
{
	return RootSceneComp->GetComponentLocation() +
		(GetActorRightVector() + GetActorUpVector() + GetActorForwardVector()) * BlockSize / 2;
}

FVector AVCBaseBlock::GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal) const
{
	return (ClickedLocation + Normal * BlockSize / 2).GridSnap(BlockSize);
}

void AVCBaseBlock::GridSnapBlock()
{
	SetActorLocation(GetActorLocation().GridSnap(BlockSize));
}

void AVCBaseBlock::DeleteInstancedMesh() const
{
	AVCGameModeBase* GM = Cast<AVCGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		AVCProceduralGenerator* ProceduralGenerator = GM->GetProceduralGenerator();
		if (ProceduralGenerator)
		{
			ProceduralGenerator->GetInstancedStaticMeshComponent()->RemoveInstance(SMInstanceIndex);
		}
	}
}

void AVCBaseBlock::MoveInstancedMesh(const FTransform& NewTransform) const
{
	AVCGameModeBase* GM = Cast<AVCGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		AVCProceduralGenerator* ProceduralGenerator = GM->GetProceduralGenerator();
		if (ProceduralGenerator)
		{
			ProceduralGenerator->GetInstancedStaticMeshComponent()->UpdateInstanceTransform(SMInstanceIndex, NewTransform, true);
		}
	}
}

void AVCBaseBlock::SetStaticMeshInstanceID(int32 ID)
{
	SMInstanceIndex = ID;
}
