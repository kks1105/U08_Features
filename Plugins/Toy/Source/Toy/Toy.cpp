
#include "Toy.h"

#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("startuptoymodule"));

	Extender = MakeShareable(new FExtender()); //�޸��Ҵ絥���Ϳø���
	FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this,&FToyModule::AddToolBar);//�̺�Ʈ��������Ʈ ũ������Ʈ,��ġ,��������Ʈ�̸�
	
	Extender->AddToolBarExtension("Compile",EExtensionHook::Before,nullptr,toolBarExtensionDelegate);//���ٿ����̱�:���ϰ��̸�,������ġ,�Ҹ��,


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