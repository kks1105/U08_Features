
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"


class TOY_API SMeshViewer_Viewport : public SEditorViewport,public FGCObject
{
public:
	SMeshViewer_Viewport();

	void Construct(const FArguments& InArgs); //부모에있는거지만 가상함수가아니지만 그냥쓰면 써짐 SNew쓸때 호출됨

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override; //가비지컬렉터에있는 가비지컬렉터관리함수


protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override; //s에디터에있는 클라이언트(카메라등등)객체 을 만들어주는함수
public:
	TSharedRef<class FAdvancedPreviewScene> GetScene();//밑에씬받는용


private:
	//Scene
	TSharedPtr<class FAdvancedPreviewScene> Scene;//씬객체
	//Client
	TSharedPtr<class FMeshViewer_Viewport_Client> ViewportClient; //클라이언트객체


private:
	class UStaticMeshComponent* RobotMesh;//scene에서 보여줄메쉬 
	class UStaticMeshComponent* FloorMesh;//2




};
