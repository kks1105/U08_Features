

#include "MeshViewer_Viewport.h"
#include "MeshViewer_Viewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "Components/StaticMeshComponent.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));//씬생성  조명기타관련(기본값넣음)


}

void SMeshViewer_Viewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(InArgs);//슈퍼콜

	//floor
	UStaticMesh* floorMeshAsset = LoadObject<UStaticMesh>(nullptr,TEXT("StaticMesh'/Engine/MapTemplates/SM_Template_Map_Floor.SM_Template_Map_Floor'")); //메쉬가져오기 LoadObject씀 생성자가아니라 컨스트럭트못씀
	FloorMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient); // 컴포넌트올리기 패키징방법,이름,저장방법
	FloorMesh->SetStaticMesh(floorMeshAsset);//스태틱메쉬세팅
	
	FTransform transform;//위치
	Scene->AddComponent(FloorMesh,transform);//씬에 컴포넌트추가


	//robot
	UStaticMesh* robotMeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Robot/SM_Robot.SM_Robot'"));//가져오기
	RobotMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient); // 컴포넌트올리기 패키징방법,이름,저장방법
	RobotMesh->SetStaticMesh(robotMeshAsset);//스태틱메쉬세팅

	transform.SetLocation(FVector(0,0,150));//z150올려봄
	Scene->AddComponent(RobotMesh, transform);//컴포넌트추가


}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(RobotMesh);//가비지컬렉터에등록해서 자동삭제해줌
	Collector.AddReferencedObject(FloorMesh);//가비지컬렉터에등록해서 자동삭제해줌


}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FMeshViewer_Viewport_Client(Scene.Get(),SharedThis(this)));//뷰포트클라이언트생성 씬,뷰포트 (우리가만든거)

	return ViewportClient.ToSharedRef();
}

TSharedRef<class FAdvancedPreviewScene> SMeshViewer_Viewport::GetScene()
{
	return Scene.ToSharedRef();
}
