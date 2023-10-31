
#include "Toy.h"
#include "LevelEditor.h"
#include "GameplayDebugger.h"
#include "ToolBar/ButtonCommand.h"
#include "ToolBar/IconStyle.h"
#include "DebuggerCategory/DebuggerCategory.h"



#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("startuptoymodule"));


	//toolbar
	{
		FIconStyle::Get(); //한번호출로생성

		FButtonCommand::Register();//버튼커맨드의 레지스터실행(중복되는게없으면 레지스터커맨드실행하는함수)

		Extender = MakeShareable(new FExtender()); //메모리할당데이터올리기
		FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar_SpawnVertex);//이벤트딜리게이트 크리에이트,위치,딜리게이트이름

		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate);//툴바에붙이기:붙일곳이름,붙일위치,액션명령,붙이기딜리게이트(애드툴바)


		FToolBarExtensionDelegate toolBarExtensionDelegate2 = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar_OpenViewer);//오픈뷰어 이벤트딜리게이트 크리에이트,위치,딜리게이트이름
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate2);//오픈뷰어 툴바에붙이기:붙일곳이름,붙일위치,액션명령,붙이기딜리게이트(애드툴바)


		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");//레벨에디터 모듈가져오기 

		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);//에디터에 익스텐더붙이기

	}

	//Debugercategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); //에디터 게임플레이디버거가져오기
		IGameplayDebugger::FOnGetCategory categoryDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);//딜리게이트만들기 (디버거카테고리의 메이크인스턴스), 
		gameplayDebugger.Get().RegisterCategory("AwesomeData",categoryDelegate,EGameplayDebuggerCategoryState::EnabledInGameAndSimulate,5);//등록 이름,딜리게이트,상태,번호
		gameplayDebugger.NotifyCategoriesChanged();//정렬하려고 호출



	}


}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdowntoymodule"));

	if(IGameplayDebugger::IsAvailable()) //검사
	IGameplayDebugger::Get().UnregisterCategory("AwesomeData");//어썸데이터해제


	FIconStyle::Shutdown();//아이콘스타일의 셧다운실행(인스턴스변수 초기화)

}



void FToyModule::AddToolBar_SpawnVertex(FToolBarBuilder& InToolBarBuilder)
{

	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //아이콘이름 SlateEditorStyle에있는거가져옴

	

	InToolBarBuilder.AddSeparator();//줄긑기
	//InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().SpawnVertexButton, NAME_None, FText::FromString("spawn vertex"), FText::FromString("spawn vertex from binarty file"), icon);//이름,훅네임,라벨이름(보이는글자),?,아이콘

	InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().SpawnVertexButton, NAME_None, FText::FromString("spawn vertex"), FText::FromString("spawn vertex from binarty file"), FIconStyle::Get()->SpawnVertexButtonIcon);//버튼추가 이름,훅네임,라벨이름(보이는글자),?,아이콘(아이콘스타일의 스폰버택스아이콘(리소스스폰버택스아이콘))

}


void FToyModule::AddToolBar_OpenViewer(FToolBarBuilder& InToolBarBuilder)
{


	//InToolBarBuilder.AddSeparator();//줄긑기

	InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().OpenViewerButton, NAME_None, FText::FromString("Open Viewer"), FText::FromString("Open Customization Viewer"), FIconStyle::Get()->OpenViewerButtonIcon);//버튼추가 이름,훅네임,라벨이름(보이는글자),?,아이콘(아이콘스타일의 스폰버택스아이콘(리소스스폰버택스아이콘))



}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)