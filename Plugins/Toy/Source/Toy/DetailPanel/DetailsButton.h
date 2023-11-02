
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class TOY_API FDetailsButton :public IDetailCustomization
{
public:
	static TSharedRef<class IDetailCustomization> MakeInstance();//����cpp ��������Ʈ

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;//IDetailCustomization���ִ� �������г� ��ġ���Լ�


private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveVertexData();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
