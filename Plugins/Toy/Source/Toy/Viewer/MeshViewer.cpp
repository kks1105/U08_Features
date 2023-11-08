
#include "MeshViewer.h"
#include "MeshViewer_Viewport.h"
#include "AdvancedPreviewSceneModule.h"

TSharedPtr<FMeshViewer> FMeshViewer::Instance = nullptr;
const static FName ToolkitName = TEXT("MeshViewer");
const static FName ViewportTabID = TEXT("Viewport");
const static FName PreviewTabID = TEXT("Preview");
const static FName DetailsTabID = TEXT("Details");

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

void FMeshViewer::Shutdown()
{
	if (Instance.IsValid())
	{
		Instance->CloseWindow();//한번실행됬으면 (저장값있으면) 클로즈윈도우
	}

}

void FMeshViewer::OpenWindow_Internal(UObject* InAsset)
{
	//create slatewidget
	ViewportWidget = SNew(SMeshViewer_Viewport);//메쉬뷰어뷰포트 만들기

	FAdvancedPreviewSceneModule& previewSceneSettings = FModuleManager::LoadModuleChecked<FAdvancedPreviewSceneModule>("AdvancedPreviewScene");  //프리뷰씬모듈가져오기

	PreviewSceneSettingsWidget = previewSceneSettings.CreateAdvancedPreviewSceneSettingsWidget(ViewportWidget->GetScene()); //프리뷰씬만들기

	FPropertyEditorModule& properyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor"); //디테일패널모듈가져오기
	FDetailsViewArgs args(false,false,true,FDetailsViewArgs::ObjectsUseNameArea);//디테일패널세팅
	DetailsViewWidget = properyEditor.CreateDetailView(args);//만들기 디테일패널
	DetailsViewWidget->SetObject(InAsset);//세팅


	//creat layout
	TSharedRef<FTabManager::FLayout> layout = FTabManager::NewLayout("MeshViewer_Layout")
		->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		//Toolbar붙이기
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.1f)
			->AddTab(GetToolbarTabId(),ETabState::OpenedTab) 
		)
		//Panel(대)붙이기
		->Split
		(
			FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
			//중viewport
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.75f)
				->AddTab(ViewportTabID, ETabState::OpenedTab)
				

			)//end(중) viewport
			//중RightPanel
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.25f)
				//(소)preview
				->Split
				(
					FTabManager::NewStack()
					->AddTab(PreviewTabID, ETabState::OpenedTab)
				)
				//(소)Detatils
				->Split
				(
					FTabManager::NewStack()
					->AddTab(DetailsTabID, ETabState::OpenedTab)
				)
			)//end(중)
		)//END(대)
	);//디테일패널에붙을 탭 붙이기 FTabManager::NewSplitter()영역나누기 FTabManager::NewStack()붙이기 ->Split만들기
	

	//open  slate window
	FAssetEditorToolkit::InitAssetEditor
	(
		EToolkitMode::Standalone/*별도의 창으로*/,
		TSharedPtr<IToolkitHost>(),
		ToolkitName,
		layout,
		true/*검색창*/,
		true/*툴바아이콘*/,
		InAsset
	);//실제창띄우는거    창정보,호스트?,툴바이름 , ui정보,검색창여부,툴바아이콘여부,
}

void FMeshViewer::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	//add탭(ui붙이는거)이호출되면 자동으로들어와짐
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	FOnSpawnTab viewportSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_ViewportTab);//딜리게이트
	TabManager->RegisterTabSpawner(ViewportTabID, viewportSpawnEvent);//레이아웃에서 탭아이디를가져와구별하고 

	FOnSpawnTab previewSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_PreviewSceneSettingsTab);//딜리게이트
	TabManager->RegisterTabSpawner(PreviewTabID, previewSpawnEvent);//레이아웃에서 탭아이디를가져와구별하고 

	FOnSpawnTab detailsSpawnEvent = FOnSpawnTab::CreateSP(this, &FMeshViewer::Spawn_DetailsViewTab);//딜리게이트
	TabManager->RegisterTabSpawner(DetailsTabID, detailsSpawnEvent);//레이아웃에서 탭아이디를가져와구별하고 

}

TSharedRef<SDockTab> FMeshViewer::Spawn_ViewportTab(const FSpawnTabArgs& InArgs)
{
	


	return SNew(SDockTab)
		[
			ViewportWidget.ToSharedRef()//탭에뷰포트붙음
		]; //뷰포트에 SDockTab이붙음 (slate위젯으로붙이는거다할수있음)
}

TSharedRef<SDockTab> FMeshViewer::Spawn_PreviewSceneSettingsTab(const FSpawnTabArgs& InArgs)
{
	return SNew(SDockTab)
		[
			PreviewSceneSettingsWidget.ToSharedRef()//2프리뷰
		]; //뷰포트에 SDockTab이붙음 (slate위젯으로붙이는거다할수있음)
}

TSharedRef<SDockTab> FMeshViewer::Spawn_DetailsViewTab(const FSpawnTabArgs& InArgs)
{

	return SNew(SDockTab)
		[
			DetailsViewWidget.ToSharedRef()//3디테일
		]; //뷰포트에 SDockTab이붙음 (slate위젯으로붙이는거다할수있음)
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

	//뭔지모름
	return FLinearColor();
}
