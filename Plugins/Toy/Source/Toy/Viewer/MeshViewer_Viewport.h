
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"


class TOY_API SMeshViewer_Viewport : public SEditorViewport,public FGCObject
{
public:
	SMeshViewer_Viewport();

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override; //�������÷��Ϳ��ִ� �������÷��Ͱ����Լ�

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override; //s�����Ϳ��ִ� Ŭ���̾�Ʈ(ī�޶���)��ü �� ������ִ��Լ�

private:
	class UStaticMeshComponent* RobotMesh;//scene���� �����ٸ޽� 
	class UStaticMeshComponent* FloorMesh;//2


};
