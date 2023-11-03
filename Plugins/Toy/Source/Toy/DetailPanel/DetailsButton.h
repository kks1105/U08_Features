
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
	}//�����ڿ����ε� <<(�ѱ��) FArchive(�а��� �𸮾���(>>)����)  FVertexData���籸��ü  
};

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
