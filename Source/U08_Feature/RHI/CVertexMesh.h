
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertexMesh.generated.h"

UCLASS()
class U08_FEATURE_API ACVertexMesh : public AActor
{
	GENERATED_BODY()
	
public:	

	ACVertexMesh();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* ProcMesh;


private:
	TArray<FVector> Positions;//포지션저장용
	TArray<int32> Indices;//제이슨시리얼어쩌구 삼각좌표저장용
	TArray<FVector> Normals;//노멀벡터저장용
	TArray<FVector2D> UVs; //정점그릴때 uv좌표저장용
	TArray<FColor> Colors; //색저장용



};
