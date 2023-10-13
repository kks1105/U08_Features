

#include "CVertexMesh.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACVertexMesh::ACVertexMesh()
{
 	
	PrimaryActorTick.bCanEverTick = true;


	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh"); //컴포넌트만들기 프로시듀얼타입임

	float p = 0.5f;

	Positions.Add(FVector(-p, -p, -p));//정점위치 왼아래   부터 오아래까지
	Positions.Add(FVector(-p, -p, +p));//왼위
	Positions.Add(FVector(-p, +p, -p));//오아래
	Positions.Add(FVector(-p, +p, +p));//오위

	for (int32 i = 0; i < 4; i++)
	{
		Normals.Add(FVector(-1, 0, 0));//노멀벡터넣기
	}

	Colors.Add(FColor::Red);//색넣기
	Colors.Add(FColor::Green);
	Colors.Add(FColor::Blue);
	Colors.Add(FColor::Orange);


	UVs.Add(FVector2D(0, 1));//uv좌표넣기
	UVs.Add(FVector2D(0, 0));
	UVs.Add(FVector2D(1, 1));
	UVs.Add(FVector2D(1, 0));

	Indices.Add(2);//면그릴삼각형 인덱스어래이에추가하기 언리얼 정점면그릴땐 반시계방향 오아래
	Indices.Add(1);//왼위
	Indices.Add(0);//왼아래

	Indices.Add(3);//오위
	Indices.Add(1);//왼위
	Indices.Add(2);//오아래



	ProcMesh->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(), true);//정점에면만들기 인덱스번호,정점,인덱스,노멀벡터,uv좌표,색,탄젠트벡터(기본값),충돌체여부 
}


void ACVertexMesh::BeginPlay()
{
	Super::BeginPlay();
	
}


void ACVertexMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

