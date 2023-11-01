
#include "CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"


ACButtonActor::ACButtonActor()
{
	CHelpers::CreateSceneComponent(this, &Mesh, "Mesh"); //루트에 메쉬 메쉬이름으로만들기붙이기

	UStaticMesh* meshAsset; //스태틱메쉬  
	CHelpers::GetAsset<UStaticMesh>(&meshAsset, "StaticMesh'/Game/StaticMeshes/SM_Merged.SM_Merged'");//에셋가져오기 스태틱메쉬, 경로
	
	UMaterialInstanceConstant* materialAsset; //머티리얼 
	CHelpers::GetAsset<UMaterialInstanceConstant>(&materialAsset, "MaterialInstanceConstant'/Game/Materials/Surface/MAT_Shuffle.MAT_Shuffle'"); //가져오기 머티리얼인스턴스콘스탄트타입, 경로
	Mesh->SetStaticMesh(meshAsset);//스태틱메쉬 세팅
	Mesh->SetMaterial(0,materialAsset);//머티리얼 0번위치에 세팅
 
}


void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}


