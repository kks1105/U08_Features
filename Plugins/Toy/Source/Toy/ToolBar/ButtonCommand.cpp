

#include "ButtonCommand.h"
#include "EditorStyleSet.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Serialization/BufferArchive.h"
#include "DetailPanel/DetailsButton.h"

FButtonCommand::FButtonCommand():TCommands("ContextName",FText::FromString("ContextDesc"),NAME_None,FEditorStyle::GetStyleSetName())
{
	SpawnVertexCommand = MakeShareable(new FUICommandList());//��ưĿ�ǵ�ø��⸸���

}

FButtonCommand::~FButtonCommand() 
{
	
	if (SpawnVertexCommand.IsValid())//���̳ʽ��ƴҶ���
		SpawnVertexCommand.Reset();//���۷���ī��Ʈ���(���������Ʈ ī��Ʈ)

}

void FButtonCommand::RegisterCommands()
{

	//Todo. ��ưUI(CommandInfo) �����ϱ� (Spawn Vertex)
#define LOCTEXT_NAMESPACE "" //�ٱ������������ѳ��ӽ����̽� Ű����������

	UI_COMMAND(SpawnVertexButton," SpawnVertexButton"," Spawn Vertex Button",EUserInterfaceActionType::Button,FInputChord());//������ġ(Ŀ�ǵ�idŸ��),?,?,�������̽�Ÿ��,����Ű����Ű ����������
	UI_COMMAND(OpenViewerButton, "  OpenViewerButton", "  Open Viewer Button", EUserInterfaceActionType::Button, FInputChord());//������ġ(Ŀ�ǵ�idŸ��),?,?,�������̽�Ÿ��,����Ű����Ű ����������


#undef LOCTEXT_NAMESPACE 

	SpawnVertexCommand->MapAction(SpawnVertexButton, FExecuteAction::CreateRaw(this, &FButtonCommand::SpawnVertexButton_Pressed));//��ưĿ�ǵ�׼Ǹ����,��ġ,�׼ǽ��೻��,
	SpawnVertexCommand->MapAction(OpenViewerButton, FExecuteAction::CreateRaw(this, &FButtonCommand::OpenViewerButton_Pressed));//��ưĿ�ǵ�׼Ǹ����,��ġ,�׼ǽ��೻��,


}

void FButtonCommand::SpawnVertexButton_Pressed()
{
	//UE_LOG(LogTemp, Error, TEXT("SpawnVertexButton_Pressed"));//dpfj�α����

	//TArray<const FSlateBrush*> brushes;
	//FEditorStyle::GetResources(brushes);//�𸮾󿡵��͸��ҽ���������
	
	//for (const auto& brush : brushes)
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *brush->GetResourceName().ToString());//�귯���Ǹ��ҽ��������

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();//������â���������Լ� ���� �������ڵ鰡�������Լ�

	FString path;//�ؿ�����������
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->OpenFileDialog(handle, "Load", path, "", "Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);//���Ͽ�����(���������θ����ߵ�) �������ڵ�,�̸�,�н�,����Ʈ����,����(��������Ȯ���ھտ��ִ°�),�÷���?,����Ǯ���
	if (fileNames.Num() < 1) return;//�����������ڵ�

	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);// �о���� �о�ð�,�����̸�
	FMemoryReader reader = FMemoryReader(buffer,true );//�������۸� �о�������۷ιٲ�
	buffer.Seek(0);//����ó�������б� �̰ž������̾�ع���

	FVertexData data; //����
	reader << data; //reader�� �����͵������б�           �����Ϲ�ư����� �����ڿ����ε������س��� �б�;����Ǻθ���س���
	reader.FlushCache();//�����ɰ������ �б��ε�����??
	reader.Close();//�ݱ�

	GLog->Logf(TEXT("Vertex Count :%d"), data.Positions.Num());//�����α�
	GLog->Logf(TEXT("Index Count : %d"), data.Indices.Num());//�ε����α� �����������Ҷ� ������ �������ε��� ���̳��;߼���


}

void FButtonCommand::OpenViewerButton_Pressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Viewer Button is Pressed")); //���


}
