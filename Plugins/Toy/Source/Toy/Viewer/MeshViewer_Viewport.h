
#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"


class TOY_API SMeshViewer_Viewport : public SEditorViewport,public FGCObject
{
public:
	SMeshViewer_Viewport();

	void Construct(const FArguments& InArgs); //�θ��ִ°����� �����Լ����ƴ����� �׳ɾ��� ���� SNew���� ȣ���

public:
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override; //�������÷��Ϳ��ִ� �������÷��Ͱ����Լ�


protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override; //s�����Ϳ��ִ� Ŭ���̾�Ʈ(ī�޶���)��ü �� ������ִ��Լ�
public:
	TSharedRef<class FAdvancedPreviewScene> GetScene();//�ؿ����޴¿�


private:
	//Scene
	TSharedPtr<class FAdvancedPreviewScene> Scene;//����ü
	//Client
	TSharedPtr<class FMeshViewer_Viewport_Client> ViewportClient; //Ŭ���̾�Ʈ��ü


private:
	class UStaticMeshComponent* RobotMesh;//scene���� �����ٸ޽� 
	class UStaticMeshComponent* FloorMesh;//2




};
