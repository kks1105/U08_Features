
#include "MeshViewer.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;

void FMeshViewer::OpenWindow(UObject* InAsset)
{

	if (Instance.IsValid())
	{
		Instance->CloseWindow();//�ѹ����������ϳ�����
		Instance = nullptr;
	}

	Instance = MakeShareable(new FMeshViewer());//�����
	Instance->OpenWindow_Internal(InAsset);//�������ϴ��Ͻ���

}

void FMeshViewer::Shutdow()
{
	if (Instance.IsValid())
	{
		Instance.Reset();//�ѹ����������� (���尪������)����
	}

}

void FMeshViewer::OpenWindow_Internal(UObject* InAsset)
{
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")->AddArea(FTabManager::NewPrimaryArea());//�������гο����� �� ���̱�
	
	//FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone/*������ â����*/, TSharedPtr<IToolkitHost>(), ToolkitName, layout, true/*�˻�â*/, true/*���پ�����*/, InAsset); //����â���°�

}

FName FMeshViewer::GetToolkitFName() const
{
	return FName();
}

FText FMeshViewer::GetBaseToolkitName() const
{
	return FText();
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{
	return FString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale(void) const
{
	return FLinearColor();
}
