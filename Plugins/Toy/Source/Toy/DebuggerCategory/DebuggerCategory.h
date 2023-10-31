
#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

class TOY_API FDebuggerCategory :  public FGameplayDebuggerCategory
{

public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance(); //디버그카테고리 등록용

};
