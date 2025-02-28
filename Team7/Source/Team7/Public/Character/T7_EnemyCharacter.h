#pragma once

#include "CoreMinimal.h"
#include "T7_CharacterBase.h"
#include "T7_EnemyCharacter.generated.h"

UCLASS()
class TEAM7_API AT7_EnemyCharacter : public AT7_CharacterBase
{
	GENERATED_BODY()
	
public:
	AT7_EnemyCharacter();

private:
	virtual void Dead() override;

};
