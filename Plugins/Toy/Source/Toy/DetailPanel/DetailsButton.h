
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FDetailsButton :public IDetailCustomization
{
public:
	TSharedRef<class IDetailCustomization> MakeInstance();//����cpp ��������Ʈ

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;//IDetailCustomization���ִ� �������г� ��ġ���Լ�

};
