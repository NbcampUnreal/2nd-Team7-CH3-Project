
#include "Weapon/T7_Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AT7_Projectile::AT7_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	CollisionBox->OnComponentHit.AddDynamic(this, &AT7_Projectile::OnHit);
	SetLifeSpan(3.0f);
}

void AT7_Projectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AT7_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AT7_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// 자기 자신과 충돌한 경우 무시
	if (OtherActor == nullptr || OtherActor == this) return;

	UGameplayStatics::ApplyDamage(OtherActor, 20.0f, GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}