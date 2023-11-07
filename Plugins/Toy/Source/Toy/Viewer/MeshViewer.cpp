
#include "MeshViewer.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("MeshViewer");
const static FName ViewportTabID = TEXT("Viewport");
const static FName PreviewTabID = TEXT("Preview");
const static FName DetailsTabID = TEXT("Details");

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

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();//�ѹ����������� (���尪������) Ŭ����������
	}

}

void FMeshViewer::OpenWindow_Internal(UObject* InAsset)
{
	//creat layout
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		//Toolbar���̱�
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->AddTab(GetToolbarTabId(),ETabState::OpenedTab) 
		)
		//Panel(��)���̱�
		->Split
		(
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			//��viewport
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.75f)
				->AddTab(ViewportTabID, ETabState::OpenedTab)
				

			)//end(��) viewport
			//��RightPanel
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.25f)
				//(��)preview
				->Split
				(
					FTabManager::NewStack()
					->AddTab(PreviewTabID, ETabState::OpenedTab)
				)
				//(��)Detatils
				->Split
				(
					FTabManager::NewStack()
					->AddTab(DetailsTabID, ETabState::OpenedTab)
				)
			)//end(��)
		)//END(��)
	);//�������гο����� �� ���̱� FTabManager::NewSplitter()���������� FTabManager::NewStack()���̱� ->Split�����
	

	//open  slate window
	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone/*������ â����*/,
		TSharedPtr<IToolkitHost>(),
		ToolkitName,
		layout,
		true/*�˻�â*/,
		true/*���پ�����*/,
		InAsset
	);//����â���°�    â����,ȣ��Ʈ?,�����̸� , ui����,�˻�â����,���پ����ܿ���,
}

void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	//add��(ui���̴°�)��ȣ��Ǹ� �ڵ����ε�����
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab viewportSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);//��������Ʈ
	TabManager->RegisterTabSpawner(ViewportTabID, viewportSpawnEvent);//���̾ƿ����� �Ǿ��̵𸦰����ͱ����ϰ� 


}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	


	return SNew(SDockTab)
		[
			SNew(SButton)
			.Text(FText::FromString("Test"))
		]; //����Ʈ�� SDockTab�̺��� (slate�������κ��̴°Ŵ��Ҽ�����)
}

FName FMeshViewer::GetToolkitFName() const
{
	return ToolkitName;
}

FText FMeshViewer::GetBaseToolkitName() const
{


	return FText::FromName(ToolkitName);
}

FString FMeshViewer::GetWorldCentricTabPrefix() const
{


	return ToolkitName.ToString();
}

FLinearColor FMeshViewer::GetWorldCentricTabColorScale(void) const
{

	//������
	return FLinearColor();
}
