

#include "ButtonCommand.h"
#include "EditorStyleSet.h"

FButtonCommand::FButtonCommand():TCommands("ContextName",FText::FromString("ContextDesc"),NAME_None,FEditorStyle::GetStyleSetName())
{
	SpawnVertexCommand = MakeShareable(new FUICommandList());//버튼커맨드올리기만들기

}

FButtonCommand::~FButtonCommand() 
{
	
	if (SpawnVertexCommand.IsValid())//마이너스아닐때만
		SpawnVertexCommand.Reset();//레퍼런스카운트깍기(쉐어드포인트 카운트)

}

void FButtonCommand::RegisterCommands()
{

	//Todo. 버튼UI(CommandInfo) 생성하기 (Spawn Vertex)
#define LOCTEXT_NAMESPACE "" //다국어지원을위한네임스페이스 키없으면비워놈

	UI_COMMAND(SpawnVertexButton," SpawnVertexButton"," Spawn Vertex Button",EUserInterfaceActionType::Button,FInputChord());//저장위치(커맨드id타입),?,?,인터페이스타입,단축키조합키 없으면비워놈
	UI_COMMAND(OpenViewerButton, "  OpenViewerButton", "  Open Viewer Button", EUserInterfaceActionType::Button, FInputChord());//저장위치(커맨드id타입),?,?,인터페이스타입,단축키조합키 없으면비워놈


#undef LOCTEXT_NAMESPACE 

	SpawnVertexCommand->MapAction(SpawnVertexButton, FExecuteAction::CreateRaw(this, &FButtonCommand::SpawnVertexButton_Pressed));//버튼커맨드액션만들기,위치,액션실행내용,
	SpawnVertexCommand->MapAction(OpenViewerButton, FExecuteAction::CreateRaw(this, &FButtonCommand::OpenViewerButton_Pressed));//버튼커맨드액션만들기,위치,액션실행내용,


}

void FButtonCommand::SpawnVertexButton_Pressed()
{
	//UE_LOG(LogTemp, Error, TEXT("SpawnVertexButton_Pressed"));//dpfj로그찍기

	TArray<const FSlateBrush*> brushes;
	FEditorStyle::GetResources(brushes);//언리얼에디터리소스가져오기
	
	for (const auto& brush : brushes)
		UE_LOG(LogTemp, Warning, TEXT("%s"), *brush->GetResourceName().ToString());//브러쉬의리소스네임찍기

}

void FButtonCommand::OpenViewerButton_Pressed()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Viewer Button is Pressed")); //출력


}
