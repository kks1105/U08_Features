
#include "CLoadMesh.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ProceduralMeshComponent.h"

ACLoadMesh::ACLoadMesh()
{
	bRunConstructionScriptOnDrag = false;//원래는 드래그시에도호출되는데 이옵션끄면 처음올릴때만호출됨

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");//생성 프록메쉬
}


void ACLoadMesh::OnConstruction(const FTransform& Transform)
{

	Super::OnConstruction(Transform);

	ProcMesh->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(),true);//프록메쉬생성 //정점에면만들기 인덱스번호,정점,인덱스,노멀벡터,uv좌표,색,탄젠트벡터(기본값),충돌체여부 

	CHelpers::GetAssetDynamic(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Gold.MAT_Gold'"); //가져오기
	ProcMesh->SetMaterial(0, Material); //머티리엘0번에셋팅
}

void ACLoadMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACLoadMesh::SetPositions(const TArray<FVector>& InPositions)
{
	Positions = InPositions; //포지션값본체저장
}

void ACLoadMesh::SetNormals(const TArray<FVector>& InNormals)
{
	Normals = InNormals;//위와같음
}

void ACLoadMesh::SetColors(const TArray<FColor>& InColors)
{
	Colors = InColors;//위와같음
}

void ACLoadMesh::SetUVs(const TArray<FVector2D>& InUVs)
{
	UVs = InUVs;//위와같음


}

void ACLoadMesh::SetIndices(const TArray<int32>& InIndices)
{
	Indices = InIndices;//위와같음
}


