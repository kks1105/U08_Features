
#include "Toy.h"
#include "LevelEditor.h"
#include "ToolBar/ButtonCommand.h"


#define LOCTEXT_NAMESPACE "FToyModule"

void FToyModule::StartupModule()
{
	UE_LOG(LogTemp, Error, TEXT("startuptoymodule"));

	FButtonCommand::Register();//��ưĿ�ǵ��� �������ͽ���(�ߺ��Ǵ°Ծ����� ��������Ŀ�ǵ�����ϴ��Լ�)

	Extender = MakeShareable(new FExtender()); //�޸��Ҵ絥���Ϳø���
	FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this,&FToyModule::AddToolBar);//�̺�Ʈ��������Ʈ ũ������Ʈ,��ġ,��������Ʈ�̸�
	
	Extender->AddToolBarExtension("Compile",EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand,toolBarExtensionDelegate);//���ٿ����̱�:���ϰ��̸�,������ġ,�׼Ǹ��,���̱��������Ʈ

	FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");//���������� ��Ⱑ������ 

	levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);//�����Ϳ� �ͽ��ٴ����̱�
}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdowntoymodule"));

}

void FToyModule::AddToolBar(FToolBarBuilder& InToolBarBuilder)
{

	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //�������̸� SlateEditorStyle���ִ°Ű�����

	InToolBarBuilder.AddSeparator();//�كP��
	InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().SpawnVertexButton, NAME_None, FText::FromString("spawn vertex"), FText::FromString("spawn vertex from binarty file"), icon);//�̸�,�ų���,���̸�(���̴±���),?,������

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)