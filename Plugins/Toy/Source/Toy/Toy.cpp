
#include "Toy.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("startuptoymodule"));

	Extender = MakeShareable(new FExtender()); //메모리할당데이터올리기
	FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this,&FToyModule::AddToolBar);//이벤트딜리게이트 크리에이트,위치,딜리게이트이름
	
	Extender->AddToolBarExtension("Compile",EExtensionHook::Before,nullptr,toolBarExtensionDelegate);//툴바에붙이기:붙일곳이름,붙일위치,할명령,


}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdowntoymodule"));

}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{


}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)