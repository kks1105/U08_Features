

#include "ButtonCommand.h"
#include "EditorStyleSet.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Serialization/BufferArchive.h"
#include "DetailPanel/DetailsButton.h"
#include "LevelEditorViewport.h"
#include "RHI/CLoadMesh.h"
#include "Misc/FileHelper.h"
#include "Viewer/MeshViewer.h"
#include "Assets/CDetailAsset.h"


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

	//TArray<const FSlateBrush*> brushes;
	//FEditorStyle::GetResources(brushes);//언리얼에디터리소스가져오기
	
	//for (const auto& brush : brushes)
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *brush->GetResourceName().ToString());//브러쉬의리소스네임찍기

	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle();//윈도우창가져오는함수 에서 윈도우핸들가져오는함수

	FString path;//밑에넣을려고만듦
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();
	platform->OpenFileDialog(handle, "Load", path, "", "Binary File(*.bin)|*.bin", EFileDialogFlags::None, fileNames);//파일열기방식(저장은따로만들어야됨) 윈도우핸들,이름,패스,디폴트파일,필터(파일형식확장자앞에있는거),플래그?,파일풀경로
	if (fileNames.Num() < 1) return;//저장없으면언핸들

	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *fileNames[0]);// 읽어오기 읽어올거,파일이름
	FMemoryReader reader = FMemoryReader(buffer,true );//저장용버퍼를 읽어오기용버퍼로바꿈
	buffer.Seek(0);//버퍼처음부터읽기 이거없으면이어서해버림

	FVertexData data; //계산용
	reader << data; //reader로 데이터데이터읽기           디테일버튼헤더에 연산자오버로딩정의해놓음 읽기와쓰기의부모로해놨음
	reader.FlushCache();//누적될거지우기 읽기인데있음??
	reader.Close();//닫기

	GLog->Logf(TEXT("Vertex Count :%d"), data.Positions.Num());//정점로그
	GLog->Logf(TEXT("Index Count : %d"), data.Indices.Num());//인덱스로그 여기까지출력할때 저장한 정점과인덱스 같이나와야성공

	//->Save File(* opened.Csv 테스트용 저장해서 잘찾나확인해본거
	//FString planeText;//입력용 SaveStringToFile은 fstring으로넣야됨
	//for (int32 i = 0; i < data.Positions.Num(); i++)
	//{
	//	planeText.Append(data.Positions[i].ToString() + ",");//정점
	//	planeText.Append(data.Normals[i].ToString() + ",");//노말+띄어쓰기
	//	planeText.Append(data.UVs[i].ToString() + "\n");//텍스쳐 +줄바꿈
	//}


	//FString planeTextPath = FPaths::GetBaseFilename(fileNames[0], false);//확장자빠진풀경로 (위에서 bin붙여서안빼면 bin될수도있음)
	//planeTextPath.Append("_opened.csv"); //새로운이름으로저장 그냥뒤에안들어올수도잇어서 csv넣기
	//FFileHelper::SaveStringToFile(planeText, *planeTextPath); //csv로저장(평문) 읽을수있는거

	//spawn LoadMesh //로드한메쉬스폰CLoadMesh
	FLevelEditorViewportClient* viewportClient = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();//에디터객체에서 현재활성화된뷰포트가져오고 거기서클라이언트가져옴(기능있어서다운캐스팅함)
	FVector start = viewportClient->GetViewLocation();//라인스타트지점 클라이언트보는지점부터
	FVector end = start + viewportClient->GetViewRotation().RotateVector(FVector(10000,0,0));//끝지점 스타트 +전방방향1만지점

	UWorld* world = GEditor->GetEditorWorldContext().World();//에디터에서 월드가져오기
	FHitResult hitresult;//히트리졀트
	world->LineTraceSingleByChannel(hitresult, start, end, ECollisionChannel::ECC_Visibility); //라인트레이스 히트리졀트,스타트지점,엔드지점,보이기설정
	if (hitresult.bBlockingHit == false)
	{
		UE_LOG(LogTemp, Error, TEXT("out of ranfge!!"));//라인안부리치면 문구출력

		return;

	}

	FTransform transform;//(스폰위치) 트랜스폼
	transform.SetLocation(hitresult.ImpactPoint);//트랜스폼위치세팅(화면에서라인트레이스부리친부분)
	FVector direction = (hitresult.TraceEnd - hitresult.TraceStart).GetSafeNormal(); //부리친데서 카메라보는방향
	FRotator rotation = FRotator(0, direction.Rotation().Yaw,0);//요방향만회전
	transform.SetRotation(FQuat(rotation));//회전세팅 요방향만카메라바로보게



	ACLoadMesh* spawnedActor = world->SpawnActorDeferred<ACLoadMesh>(ACLoadMesh::StaticClass(),transform,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);//스폰디퍼드 클래스,트랜스폰, , , 스폰방법

	spawnedActor->SetPositions(data.Positions);  //포지션세팅
	spawnedActor->SetIndices(data.Indices);//2
	spawnedActor->SetNormals(data.Normals);//3
	spawnedActor->SetUVs(data.UVs);//4
	spawnedActor->SetColors(data.Colors);//5
	

	spawnedActor->FinishSpawning(transform);//스폰 트랜스폼위치로




}

void FButtonCommand::OpenViewerButton_Pressed()
{
	//UE_LOG(LogTemp, Warning, TEXT("Open Viewer Button is Pressed")); //출력
	FMeshViewer::OpenWindow(NewObject<>);//Meshviewer의 오픈윈도우


}
