
#include "CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"


ACButtonActor::ACButtonActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh"); //��Ʈ�� �޽� �޽��̸����θ������̱�

	UStaticMesh* meshAsset; //����ƽ�޽�  
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");//���°������� ����ƽ�޽�, ���
	
	//UMaterialInstanceConstant* materialAsset; //��Ƽ���� 
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Shuffle.MAT_Shuffle'"); //�������� ��Ƽ�����ν��Ͻ��ܽ�źƮŸ��, ���
	Mesh->SetStaticMesh(meshAsset);//����ƽ�޽� ����
	Mesh->SetMaterial(0, Material);//��Ƽ���� 0����ġ�� ����
 
}


void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}


#if WITH_EDITOR
void ACButtonActor::ShuffleMaterial()
{
	int32 random = UKismetMathLibrary::RandomIntegerInRange(0, (int32)EMaterialType::Max - 1); //����

	for (const auto& value : Material->TextureParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("BaseMap") == 0)
			Material->SetTextureParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].BaseMap);

		if (value.ParameterInfo.Name.Compare("NormalMap") == 0)
			Material->SetTextureParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].NormalMap);

		if (value.ParameterInfo.Name.Compare("RougnessMap") == 0)
			Material->SetTextureParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].RoughnessMap);
	}

	for (const auto& value : Material->ScalarParameterValues)
	{
		if (value.ParameterInfo.Name.Compare("MeTalic") == 0) //��Ƽ�����Ķ�����ϰ����ؾ������
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Metalic);//��Ÿ���̶��̸�ã�Ƽ� �����ϱ� ������ ��Ż��������

		if (value.ParameterInfo.Name.Compare("Lerphness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Roughness_Min); //�����Ͻ��ο� ����

		if (value.ParameterInfo.Name.Compare("Lerphness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Roughness_Max); //�����Ͻ��ƽ��� ����
	}

}
#endif
