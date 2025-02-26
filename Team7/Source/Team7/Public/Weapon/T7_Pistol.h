
#pragma once

#include "CoreMinimal.h"
#include "Weapon/T7_Weapon.h"
#include "T7_Pistol.generated.h"

/**
 * 
 */
UCLASS()
class TEAM7_API AT7_Pistol : public AT7_Weapon
{
	GENERATED_BODY()
	
public:
	AT7_Pistol();

	virtual void Fire() override;
};
