
#include "MeshViewer.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;

void FMeshViewer::OpenWindow(UObject* InAsset)
{

	if (Instance.IsValid())
	{
		Instance->CloseWindow();//한번열렸으면하나닫음
		Instance = nullptr;
	}

	Instance = MakeShareable(new FMeshViewer());//만들고
	Instance->OpenWindow_Internal(InAsset);//열릴때하는일실행

}

void FMeshViewer::Shutdow()
{
	if (Instance.IsValid())
	{
		Instance.Reset();//한번실행됬으면 (저장값있으면)리셋
	}

}

void FMeshViewer::OpenWindow_Internal(UObject* InAsset)
{
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")->AddArea(FTabManager::NewPrimaryArea());//디테일패널에붙을 탭 붙이기
	
	//FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone/*별도의 창으로*/, TSharedPtr<IToolkitHost>(), ToolkitName, layout, true/*검색창*/, true/*툴바아이콘*/, InAsset); //실제창띄우는거

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
