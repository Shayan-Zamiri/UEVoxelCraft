#include "VCBaseBlock.h"
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

	SMComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMComp"));
	SMComp->SetSimulatePhysics(false);
	SMComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SMComp->SetRelativeLocation(FVector{BlockSize / 2, BlockSize / 2, 0.0f}); // set corner of static mesh exactly on RootSceneComp
	SMComp->SetupAttachment(RootSceneComp);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetCollisionProfileName("BlockAll");
	BoxComp->SetBoxExtent(FVector{BlockSize / 2, BlockSize / 2, BlockSize / 2});
	BoxComp->SetRelativeLocation(FVector{0.0f, 0.0f, /*because of SM_Cube's pivot*/ BlockSize / 2});
	BoxComp->SetupAttachment(SMComp);
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

FVector AVCBaseBlock::GetAttachLocation(const FVector& ClickedLocation, const FVector& Normal) { return ((ClickedLocation + Normal) - BlockSize / 2).GridSnap(BlockSize); }

void AVCBaseBlock::GridSnapBlock() { SetActorLocation(GetActorLocation().GridSnap(BlockSize)); }
