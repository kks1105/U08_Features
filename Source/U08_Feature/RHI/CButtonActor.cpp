
#include "CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"


ACButtonActor::ACButtonActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh"); //��Ʈ�� �޽� �޽��̸����θ������̱�

	UStaticMesh* meshAsset; //����ƽ�޽�  
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");//���°������� ����ƽ�޽�, ���
	
	UMaterialInstanceConstant* materialAsset; //��Ƽ���� 
	CHelpers::GetAsset<UMaterialInstanceConstant>(&materialAsset, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Shuffle.MAT_Shuffle'"); //�������� ��Ƽ�����ν��Ͻ��ܽ�źƮŸ��, ���
	Mesh->SetStaticMesh(meshAsset);//����ƽ�޽� ����
	Mesh->SetMaterial(0,materialAsset);//��Ƽ���� 0����ġ�� ����
 
}


void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}


