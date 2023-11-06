
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLoadMesh.generated.h"

UCLASS()
class U08_FEATURE_API ACLoadMesh : public AActor
{
	GENERATED_BODY()
	
public:	

	ACLoadMesh();


	virtual void OnConstruction(const FTransform& Transform) override;//����Ʈ�����Լ� �������̵��Ѱ� ������Ʈ����������ǵ������

protected:

	virtual void BeginPlay() override;

public:
	void SetPositions(const TArray<FVector>& InPositions);//�ؿ������纯�� �������������������� ��ü�����ϴ��Լ�
	void SetNormals(const TArray<FVector>& InNormals);//�ؿ������纯�� ��ü�����ϴ��Լ�
	void SetColors(const TArray<FColor>& InColors);//�ؿ������纯�� ��ü�����ϴ��Լ�
	void SetUVs(const TArray<FVector2D>& InUVs);//�ؿ������纯�� ��ü�����ϴ��Լ�
	void SetIndices(const TArray<int32>& InIndices);//�ؿ������纯�� ��ü�����ϴ��Լ�



private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh; 

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;

private:
	TArray<FVector> Positions; //�������г������������ ����ü �迭�������Һ���
	TArray<FVector> Normals;//2�������г������������ ����ü �迭�������Һ���
	TArray<FColor> Colors;//3�������г������������ ����ü �迭�������Һ���
	TArray<FVector2D> UVs;//4�������г������������ ����ü �迭�������Һ���
	TArray<int32> Indices;//5�������г������������ ����ü �迭�������Һ���


};
