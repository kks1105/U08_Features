
#include "CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"


ACButtonActor::ACButtonActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh"); //루트에 메쉬 메쉬이름으로만들기붙이기

	UStaticMesh* meshAsset; //스태틱메쉬  
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");//에셋가져오기 스태틱메쉬, 경로
	
	//UMaterialInstanceConstant* materialAsset; //머티리얼 
	CHelpers::GetAsset<UMaterialInstanceConstant>(&Material, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Shuffle.MAT_Shuffle'"); //가져오기 머티리얼인스턴스콘스탄트타입, 경로
	Mesh->SetStaticMesh(meshAsset);//스태틱메쉬 세팅
	Mesh->SetMaterial(0, Material);//머티리얼 0번위치에 세팅
 
}


void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}


#if WITH_EDITOR
void ACButtonActor::ShuffleMaterial()
{
	int32 random = UKismetMathLibrary::RandomIntegerInRange(0, (int32)EMaterialType::Max - 1); //랜덤

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
		if (value.ParameterInfo.Name.Compare("MeTalic") == 0) //머티리얼파라미터하고같이해야적용됨
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Metalic);//메타릭이란이름찾아서 세팅하기 벨류에 메탈릭에랜덤

		if (value.ParameterInfo.Name.Compare("Lerphness_Min") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Roughness_Min); //러프니스민에 랜덤

		if (value.ParameterInfo.Name.Compare("Lerphness_Max") == 0)
			Material->SetScalarParameterValueEditorOnly(value.ParameterInfo, MaterialParameters[random].Roughness_Max); //러프니스맥스에 랜덤
	}

}
#endif
