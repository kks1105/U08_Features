

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

	//->Save File(* opened.Csv �׽�Ʈ�� �����ؼ� ��ã��Ȯ���غ���
	//FString planeText;//�Է¿� SaveStringToFile�� fstring���γ־ߵ�
	//for (int32 i = 0; i < data.Positions.Num(); i++)
	//{
	//	planeText.Append(data.Positions[i].ToString() + ",");//����
	//	planeText.Append(data.Normals[i].ToString() + ",");//�븻+����
	//	planeText.Append(data.UVs[i].ToString() + "\n");//�ؽ��� +�ٹٲ�
	//}


	//FString planeTextPath = FPaths::GetBaseFilename(fileNames[0], false);//Ȯ���ں���Ǯ��� (������ bin�ٿ����Ȼ��� bin�ɼ�������)
	//planeTextPath.Append("_opened.csv"); //���ο��̸��������� �׳ɵڿ��ȵ��ü����վ csv�ֱ�
	//FFileHelper::SaveStringToFile(planeText, *planeTextPath); //csv������(��) �������ִ°�

	//spawn LoadMesh //�ε��Ѹ޽�����CLoadMesh
	FLevelEditorViewportClient* viewportClient = (FLevelEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();//�����Ͱ�ü���� ����Ȱ��ȭ�Ⱥ���Ʈ�������� �ű⼭Ŭ���̾�Ʈ������(����־�ٿ�ĳ������)
	FVector start = viewportClient->GetViewLocation();//���ν�ŸƮ���� Ŭ���̾�Ʈ������������
	FVector end = start + viewportClient->GetViewRotation().RotateVector(FVector(10000,0,0));//������ ��ŸƮ +�������1������

	UWorld* world = GEditor->GetEditorWorldContext().World();//�����Ϳ��� ���尡������
	FHitResult hitresult;//��Ʈ����Ʈ
	world->LineTraceSingleByChannel(hitresult, start, end, ECollisionChannel::ECC_Visibility); //����Ʈ���̽� ��Ʈ����Ʈ,��ŸƮ����,��������,���̱⼳��
	if (hitresult.bBlockingHit == false)
	{
		UE_LOG(LogTemp, Error, TEXT("out of ranfge!!"));//���ξȺθ�ġ�� �������

		return;

	}

	FTransform transform;//(������ġ) Ʈ������
	transform.SetLocation(hitresult.ImpactPoint);//Ʈ��������ġ����(ȭ�鿡������Ʈ���̽��θ�ģ�κ�)
	FVector direction = (hitresult.TraceEnd - hitresult.TraceStart).GetSafeNormal(); //�θ�ģ���� ī�޶󺸴¹���
	FRotator rotation = FRotator(0, direction.Rotation().Yaw,0);//����⸸ȸ��
	transform.SetRotation(FQuat(rotation));//ȸ������ ����⸸ī�޶�ٷκ���



	ACLoadMesh* spawnedActor = world->SpawnActorDeferred<ACLoadMesh>(ACLoadMesh::StaticClass(),transform,nullptr,nullptr,ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);//�������۵� Ŭ����,Ʈ������, , , �������

	spawnedActor->SetPositions(data.Positions);  //�����Ǽ���
	spawnedActor->SetIndices(data.Indices);//2
	spawnedActor->SetNormals(data.Normals);//3
	spawnedActor->SetUVs(data.UVs);//4
	spawnedActor->SetColors(data.Colors);//5
	

	spawnedActor->FinishSpawning(transform);//���� Ʈ��������ġ��




}

void FButtonCommand::OpenViewerButton_Pressed()
{
	//UE_LOG(LogTemp, Warning, TEXT("Open Viewer Button is Pressed")); //���
	FMeshViewer::OpenWindow(NewObject<>);//Meshviewer�� ����������


}
