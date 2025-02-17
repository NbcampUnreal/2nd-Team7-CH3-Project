#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "T7_CharacterBase.generated.h"

// Player Character, Enemy Character 겹치는 부분 여기다 구현
// 추상 클래스로 상속받아 사용

UCLASS(Abstract)
class TEAM7_API AT7_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AT7_CharacterBase();

};
