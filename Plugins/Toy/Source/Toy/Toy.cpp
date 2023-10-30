
#include "Toy.h"
#include "LevelEditor.h"
#include "ToolBar/ButtonCommand.h"


#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("startuptoymodule"));

	FButtonCommand::Register();//버튼커맨드의 레지스터실행(중복되는게없으면 레지스터커맨드실행하는함수)

	Extender = MakeShareable(new FExtender()); //메모리할당데이터올리기
	FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this,&FToyModule::AddToolBar);//이벤트딜리게이트 크리에이트,위치,딜리게이트이름
	
	Extender->AddToolBarExtension("Compile",EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand,toolBarExtensionDelegate);//툴바에붙이기:붙일곳이름,붙일위치,액션명령,붙이기딜리게이트

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");//레벨에디터 모듈가져오기 

	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);//에디터에 익스텐더붙이기
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdowntoymodule"));

}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{

	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //아이콘이름 SlateEditorStyle에있는거가져옴

	InToolBarBuilder.AddSeparator();//줄긑기
	InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().SpawnVertexButton, NAME_None, FText::FromString("spawn vertex"), FText::FromString("spawn vertex from binarty file"), icon);//이름,훅네임,라벨이름(보이는글자),?,아이콘

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)