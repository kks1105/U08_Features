
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FDetailsButton :public IDetailCustomization
{
public:
	TSharedRef<class IDetailCustomization> MakeInstance();//토이cpp 딜리게이트

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;//IDetailCustomization에있는 디테일패널 고치는함수

};
