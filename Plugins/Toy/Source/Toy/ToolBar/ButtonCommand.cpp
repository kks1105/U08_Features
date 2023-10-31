

#include "ButtonCommand.h"
#include "EditorStyleSet.h"

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

	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);//�𸮾󿡵��͸��ҽ���������
	
	for (const auto& brush : brushes)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *brush->GetResourceName().ToString());//�귯���Ǹ��ҽ��������

}

void FButtonCommand::OpenViewerButton_Pressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Viewer Button is Pressed")); //���


}
