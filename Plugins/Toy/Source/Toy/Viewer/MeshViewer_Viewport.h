
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"


class TOY_API SMeshViewer_Viewport : public SEditorViewport,public FGCObject
{
public:
	SMeshViewer_Viewport();

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override; //가비지컬렉터에있는 가비지컬렉터관리함수

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override; //s에디터에있는 클라이언트(카메라등등)객체 을 만들어주는함수

private:
	class UStaticMeshComponent* RobotMesh;//scene에서 보여줄메쉬 
	class UStaticMeshComponent* FloorMesh;//2


};
