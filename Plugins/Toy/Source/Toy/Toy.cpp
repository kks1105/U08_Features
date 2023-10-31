
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
		FIconStyle::Get(); //�ѹ�ȣ��λ���

		FButtonCommand::Register();//��ưĿ�ǵ��� �������ͽ���(�ߺ��Ǵ°Ծ����� ��������Ŀ�ǵ�����ϴ��Լ�)

		Extender = MakeShareable(new FExtender()); //�޸��Ҵ絥���Ϳø���
		FToolBarExtensionDelegate toolBarExtensionDelegate = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar_SpawnVertex);//�̺�Ʈ��������Ʈ ũ������Ʈ,��ġ,��������Ʈ�̸�

		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate);//���ٿ����̱�:���ϰ��̸�,������ġ,�׼Ǹ��,���̱��������Ʈ(�ֵ�����)


		FToolBarExtensionDelegate toolBarExtensionDelegate2 = FToolBarExtensionDelegate::CreateRaw(this, &FToyModule::AddToolBar_OpenViewer);//���º�� �̺�Ʈ��������Ʈ ũ������Ʈ,��ġ,��������Ʈ�̸�
		Extender->AddToolBarExtension("Compile", EExtensionHook::Before, FButtonCommand::Get().SpawnVertexCommand, toolBarExtensionDelegate2);//���º�� ���ٿ����̱�:���ϰ��̸�,������ġ,�׼Ǹ��,���̱��������Ʈ(�ֵ�����)


		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");//���������� ��Ⱑ������ 

		levelEditor.GetToolBarExtensibilityManager()->AddExtender(Extender);//�����Ϳ� �ͽ��ٴ����̱�

	}

	//Debugercategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get(); //������ �����÷��̵���Ű�������
		IGameplayDebugger::FOnGetCategory categoryDelegate = IGameplayDebugger::FOnGetCategory::CreateStatic(&FDebuggerCategory::MakeInstance);//��������Ʈ����� (�����ī�װ��� ����ũ�ν��Ͻ�), 
		gameplayDebugger.Get().RegisterCategory("AwesomeData",categoryDelegate,EGameplayDebuggerCategoryState::EnabledInGameAndSimulate,5);//��� �̸�,��������Ʈ,����,��ȣ
		gameplayDebugger.NotifyCategoriesChanged();//�����Ϸ��� ȣ��



	}


}

void FToyModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, TEXT("Shutdowntoymodule"));

	if(IGameplayDebugger::IsAvailable()) //�˻�
	IGameplayDebugger::Get().UnregisterCategory("AwesomeData");//��浥��������


	FIconStyle::Shutdown();//�����ܽ�Ÿ���� �˴ٿ����(�ν��Ͻ����� �ʱ�ȭ)

}



void FToyModule::AddToolBar_SpawnVertex(FToolBarBuilder& InToolBarBuilder)
{

	FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //�������̸� SlateEditorStyle���ִ°Ű�����

	

	InToolBarBuilder.AddSeparator();//�كP��
	//InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().SpawnVertexButton, NAME_None, FText::FromString("spawn vertex"), FText::FromString("spawn vertex from binarty file"), icon);//�̸�,�ų���,���̸�(���̴±���),?,������

	InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().SpawnVertexButton, NAME_None, FText::FromString("spawn vertex"), FText::FromString("spawn vertex from binarty file"), FIconStyle::Get()->SpawnVertexButtonIcon);//��ư�߰� �̸�,�ų���,���̸�(���̴±���),?,������(�����ܽ�Ÿ���� �������ý�������(���ҽ��������ý�������))

}


void FToyModule::AddToolBar_OpenViewer(FToolBarBuilder& InToolBarBuilder)
{


	//InToolBarBuilder.AddSeparator();//�كP��

	InToolBarBuilder.AddToolBarButton(FButtonCommand::Get().OpenViewerButton, NAME_None, FText::FromString("Open Viewer"), FText::FromString("Open Customization Viewer"), FIconStyle::Get()->OpenViewerButtonIcon);//��ư�߰� �̸�,�ų���,���̸�(���̴±���),?,������(�����ܽ�Ÿ���� �������ý�������(���ҽ��������ý�������))



}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FToyModule, Toy)