

#include "MeshViewer_Viewport.h"
#include "MeshViewer_Viewport_Client.h"
#include "AdvancedPreviewScene.h"
#include "Components/StaticMeshComponent.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
	Scene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));//������  �����Ÿ����(�⺻������)


}

void SMeshViewer_Viewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(InArgs);//������

	//floor
	UStaticMesh* floorMeshAsset = LoadObject<UStaticMesh>(nullptr,TEXT("StaticMesh'/Engine/MapTemplates/SM_Template_Map_Floor.SM_Template_Map_Floor'")); //�޽��������� LoadObject�� �����ڰ��ƴ϶� ����Ʈ��Ʈ����
	FloorMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient); // ������Ʈ�ø��� ��Ű¡���,�̸�,������
	FloorMesh->SetStaticMesh(floorMeshAsset);//����ƽ�޽�����
	
	FTransform transform;//��ġ
	Scene->AddComponent(FloorMesh,transform);//���� ������Ʈ�߰�


	//robot
	UStaticMesh* robotMeshAsset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Game/Robot/SM_Robot.SM_Robot'"));//��������
	RobotMesh = NewObject<UStaticMeshComponent>(GetTransientPackage(), NAME_None, EObjectFlags::RF_Transient); // ������Ʈ�ø��� ��Ű¡���,�̸�,������
	RobotMesh->SetStaticMesh(robotMeshAsset);//����ƽ�޽�����

	transform.SetLocation(FVector(0,0,150));//z150�÷���
	Scene->AddComponent(RobotMesh, transform);//������Ʈ�߰�


}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(RobotMesh);//�������÷��Ϳ�����ؼ� �ڵ���������
	Collector.AddReferencedObject(FloorMesh);//�������÷��Ϳ�����ؼ� �ڵ���������


}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FMeshViewer_Viewport_Client(Scene.Get(),SharedThis(this)));//����ƮŬ���̾�Ʈ���� ��,����Ʈ (�츮�������)

	return ViewportClient.ToSharedRef();
}

TSharedRef<class FAdvancedPreviewScene> SMeshViewer_Viewport::GetScene()
{
	return Scene.ToSharedRef();
}
