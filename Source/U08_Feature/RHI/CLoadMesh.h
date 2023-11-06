
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


	virtual void OnConstruction(const FTransform& Transform) override;//컨스트럭션함수 오버라이드한거 원래는트랜스폰변경되도실행됨

protected:

	virtual void BeginPlay() override;

public:
	void SetPositions(const TArray<FVector>& InPositions);//밑에서만든변수 디테일페널헤더에서만든 본체에셋하는함수
	void SetNormals(const TArray<FVector>& InNormals);//밑에서만든변수 본체에셋하는함수
	void SetColors(const TArray<FColor>& InColors);//밑에서만든변수 본체에셋하는함수
	void SetUVs(const TArray<FVector2D>& InUVs);//밑에서만든변수 본체에셋하는함수
	void SetIndices(const TArray<int32>& InIndices);//밑에서만든변수 본체에셋하는함수



private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh; 

	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;

private:
	TArray<FVector> Positions; //디테일패널헤더에서만든 구조체 배열을저장할변수
	TArray<FVector> Normals;//2디테일패널헤더에서만든 구조체 배열을저장할변수
	TArray<FColor> Colors;//3디테일패널헤더에서만든 구조체 배열을저장할변수
	TArray<FVector2D> UVs;//4디테일패널헤더에서만든 구조체 배열을저장할변수
	TArray<int32> Indices;//5디테일패널헤더에서만든 구조체 배열을저장할변수


};
