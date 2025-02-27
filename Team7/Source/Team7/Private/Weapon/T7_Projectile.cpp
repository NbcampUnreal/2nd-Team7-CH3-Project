
#include "Weapon/T7_Projectile.h"
#include "Team7/Public/Character/T7_CharacterBase.h"
#include "Team7/Public/Weapon/T7_Weapon.h"  // 추가!
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
	//이러면 EnemyCharacter(ECC_Pawn)에 닿았을때 OnHit() 불리지 않음
	//CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CollisionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
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
	if (OtherActor == nullptr || OtherActor == this) return;

	float Damage = 20.0f; // 기본값

	if (const AT7_CharacterBase* Character = Cast<AT7_CharacterBase>(OtherActor))
	{
		if (const AT7_Weapon* Weapon = Character->GetCurrentWeapon())
		{
			Damage = Weapon->GetDamage();  // GetDamage()가 정상적으로 호출됨
		}
	}

	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), this, UDamageType::StaticClass());

	Destroy();
}

// GetCurrentWeapon()이 NULL임
// PlayerCharacter의 OverlappingWeapon과 CharacterBase의 CurrentWeapon를 합치는게? 

//float Damage = 0.0f;
// if (const AT7_CharacterBase* Character = Cast<AT7_CharacterBase>(OtherActor))
// {
// 	if (const AT7_Weapon* Weapon = Character->GetCurrentWeapon())
// 	{
// 		Damage = Weapon->GetDamage();	
// 	}
// }