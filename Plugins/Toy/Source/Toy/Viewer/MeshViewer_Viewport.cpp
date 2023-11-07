

#include "MeshViewer_Viewport.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(RobotMesh);//�������÷��Ϳ�����ؼ� �ڵ���������
	Collector.AddReferencedObject(FloorMesh);//�������÷��Ϳ�����ؼ� �ڵ���������


}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	return TSharedRef<FEditorViewportClient>();
}
