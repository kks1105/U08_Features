
#include "CLoadMesh.h"
#include "Global.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ProceduralMeshComponent.h"

ACLoadMesh::ACLoadMesh()
{
	bRunConstructionScriptOnDrag = false;//������ �巡�׽ÿ���ȣ��Ǵµ� �̿ɼǲ��� ó���ø�����ȣ���

	CHelpers::CreateSceneComponent(this, &ProcMesh, "ProcMesh");//���� ���ϸ޽�
}


void ACLoadMesh::OnConstruction(const FTransform& Transform)
{

	Super::OnConstruction(Transform);

	ProcMesh->CreateMeshSection(0, Positions, Indices, Normals, UVs, Colors, TArray<FProcMeshTangent>(),true);//���ϸ޽����� //�������鸸��� �ε�����ȣ,����,�ε���,��ֺ���,uv��ǥ,��,ź��Ʈ����(�⺻��),�浹ü���� 

	CHelpers::GetAssetDynamic(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Gold.MAT_Gold'"); //��������
	ProcMesh->SetMaterial(0, Material); //��Ƽ����0��������
}

void ACLoadMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACLoadMesh::SetPositions(const TArray<FVector>& InPositions)
{
	Positions = InPositions; //�����ǰ���ü����
}

void ACLoadMesh::SetNormals(const TArray<FVector>& InNormals)
{
	Normals = InNormals;//���Ͱ���
}

void ACLoadMesh::SetColors(const TArray<FColor>& InColors)
{
	Colors = InColors;//���Ͱ���
}

void ACLoadMesh::SetUVs(const TArray<FVector2D>& InUVs)
{
	UVs = InUVs;//���Ͱ���


}

void ACLoadMesh::SetIndices(const TArray<int32>& InIndices)
{
	Indices = InIndices;//���Ͱ���
}


