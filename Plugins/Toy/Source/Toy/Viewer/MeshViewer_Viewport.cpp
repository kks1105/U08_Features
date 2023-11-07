

#include "MeshViewer_Viewport.h"

SMeshViewer_Viewport::SMeshViewer_Viewport()
{
}

void SMeshViewer_Viewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(RobotMesh);//가비지컬렉터에등록해서 자동삭제해줌
	Collector.AddReferencedObject(FloorMesh);//가비지컬렉터에등록해서 자동삭제해줌


}

TSharedRef<FEditorViewportClient> SMeshViewer_Viewport::MakeEditorViewportClient()
{
	return TSharedRef<FEditorViewportClient>();
}
