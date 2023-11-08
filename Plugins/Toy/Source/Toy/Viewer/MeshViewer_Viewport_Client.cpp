

#include "MeshViewer_Viewport_Client.h"
#include "MeshViewer_Viewport.h"


FMeshViewer_Viewport_Client::FMeshViewer_Viewport_Client(FPreviewScene* InScene, const TSharedRef<SMeshViewer_Viewport>& InViewport)
	: FEditorViewportClient(nullptr, InScene,StaticCastSharedRef<SMeshViewer_Viewport>(InViewport))
{
	//카메라 세팅
	//조명 세팅...
	SetViewMode(VMI_Lit);//기본조명모드셋
	
	SetViewRotation(FRotator(-20, -90, 0));//회전설정
	SetViewLocationForOrbiting(FVector(0,0,100),1000);//오빗카메라(충돌체를뚫지못하는특징있음) 위치 ,거리
	

	


}
