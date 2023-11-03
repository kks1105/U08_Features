
#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

struct FVertexData
{
	TArray<FVector> Positions;
	TArray<FVector> Normals;
	TArray<FColor> Colors;
	TArray<FVector2D> UVs;
	TArray<int32> Indices;

	friend FArchive& operator<<(FArchive& InArchive, FVertexData& InData)
	{
		return InArchive
			<< InData.Positions
			<< InData.Normals
			<< InData.Colors
			<< InData.UVs
			<< InData.Indices;
	}//연산자오버로딩 <<(넘기기) FArchive(읽고쓰기 언리얼은(>>)없음)  FVertexData만든구조체  
};

class TOY_API FDetailsButton :public IDetailCustomization
{
public:
	static TSharedRef<class IDetailCustomization> MakeInstance();//토이cpp 딜리게이트

public:
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;//IDetailCustomization에있는 디테일패널 고치는함수


private:
	FReply OnClicked_ShuffleMaterial();
	FReply OnClicked_SaveVertexData();

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
