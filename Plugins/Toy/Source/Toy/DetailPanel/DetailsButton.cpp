

#include "DetailsButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "RHI/CButtonActor.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Serialization/BufferArchive.h"
#include "Interfaces/IMainFrameModule.h"

TSharedRef<class IDetailCustomization> FDetailsButton::MakeInstance()
{


	return MakeShareable(new FDetailsButton());
}

void FDetailsButton::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("AwesomeCategory");//���������� ī�װ��������� ���� �������������

	//Shuffle Material Button Layout
	category.AddCustomRow(FText::FromString("Shuffle material")).
		NameContent()
		[
			SNew(STextBlock).Text(FText::FromString("Shuffle material"))
		]
		.ValueContent()
		.VAlign(EVerticalAlignment::VAlign_Center)
		.MaxDesiredWidth(250)
		[
			SNew(SButton)
			.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill) //todo ��ưŬ���̺�Ʈ
			.OnClicked(this, &FDetailsButton::OnClicked_ShuffleMaterial)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Shuffle"))
			]
		];//�����߰��ϱ�+ ���������� �߰� (�������гο���) �ؽ�Ʈ��+���������� �߰�(�������гο�����) .valign����,MaxDesiredWidth�ִ�ũ�� ��ư+�ؽ�Ʈ OnClicked��������Ʈ , 


		//Save Vertex Data Button Layout
		category.AddCustomRow(FText::FromString("SaveVertex")).
			NameContent()
			[
				SNew(STextBlock).Text(FText::FromString("SaveVertex"))
			]
		.ValueContent()
			.VAlign(EVerticalAlignment::VAlign_Center)
			.MaxDesiredWidth(250)
			[
				SNew(SButton)
				.VAlign(VAlign_Center)
			.HAlign(HAlign_Fill) //todo ��ưŬ���̺�Ʈ
			.OnClicked(this, &FDetailsButton::OnClicked_SaveVertexData)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Save to Binary File"))
			]
			];//�����߰��ϱ�+ ���������� �߰� (�������гο���) �ؽ�Ʈ��+���������� �߰�(�������гο�����) .valign����,MaxDesiredWidth�ִ�ũ�� ��ư+�ؽ�Ʈ OnClicked��������Ʈ , 


		DetailBuilder.GetObjectsBeingCustomized(Objects);
}


FReply FDetailsButton::OnClicked_ShuffleMaterial()
{
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);//���̳��� ĳ��Ʈ
	if (actor == nullptr)return FReply::Unhandled(); //���������� ó���ȵȰž˸�����

	actor->ShuffleMaterial();  //��Ƽ�������Ѱ� ���������ϴ°�
	return FReply::Handled(); //ó����ٰ�˸�����
}

FReply FDetailsButton::OnClicked_SaveVertexData()
{
	//load vertex data from Sm_Asset
	//get SM Asset
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);//���̳��� ĳ��Ʈ
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());//��������
	UStaticMeshComponent* meshComp  = Cast<UStaticMeshComponent>(comp); //ĳ��Ʈ
	if (meshComp == nullptr) return FReply::Unhandled(); //ĳ��Ʈ���н� ���ڵ� 
	
	UStaticMesh* meshAsset = meshComp->GetStaticMesh();//�޽������� ����ƽ�޽���������
	if (meshAsset == nullptr) return FReply::Unhandled();// ��üũ ������ ���ڵ�
	FStaticMeshRenderData* renderData = meshAsset->RenderData.Get(); // ���������Ͱ�������
	if (renderData->LODResources.Num() < 1) return FReply::Unhandled(); //������üũ

	//GetVertexData
	FStaticMeshLODResources& lod = renderData->LODResources[0];//lod0�� =�ִ�����Ƽ ���������������� �뷮Ŀ�����۷����ι���

	FPositionVertexBuffer& positionBuffer = lod.VertexBuffers.PositionVertexBuffer; //��������ġ�����������⤤ �뷮Ŀ�����۷����ι���
	FStaticMeshVertexBuffer& metaBuffer = lod.VertexBuffers.StaticMeshVertexBuffer;//uv,normal,tanzent �ؽ��� ���� �׸��ڵ����� �뷮Ŀ�����۷����ι���
	FColorVertexBuffer& colorBuffer = lod.VertexBuffers.ColorVertexBuffer; //�����ǻ�����
	FRawStaticIndexBuffer& indexBuffer = lod.IndexBuffer; //�ε������� = ��ġ������ ����ü����ó���ؼ� �뷮����

	if(positionBuffer.GetNumVertices()<1) return FReply::Unhandled();//�����̾����� ��Ű
	if (indexBuffer.GetNumIndices() < 1) return FReply::Unhandled();//�ε��������� ��Ű

	uint32 vertexCount = positionBuffer.GetNumVertices();//���ؽ����ڰ�����
	int32 indexCount = indexBuffer.GetNumIndices(); //-�����ü����־ ��Ʈ�� �ε������ڰ�����

	GLog->Logf(TEXT("Vertex Count : %d"), vertexCount);//���ý��������ڳ������ϱ�
	GLog->Logf(TEXT("Index Count : %d"), indexCount);//�ε�������

	//Save File Dialog
	//On Save file dialog(windowAPI) ��������������â����
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle(); //������â���������Լ� ���� �������ڵ鰡�������Լ�

	FString path;//�ؿ�����������
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	platform->SaveFileDialog(handle, "Save",path,"","Binary File(*.bin)|*.bin",EFileDialogFlags::None,fileNames);//����������(���������θ����ߵ�) �������ڵ�,�̸�,�н�,����Ʈ����,����(��������Ȯ���ھտ��ִ°�),�÷���?,����Ǯ���
	if(fileNames.Num()<1) return FReply::Unhandled();//�����������ڵ�

	//GLog->Log(*fileNames[0]); //�����̸����

	TArray<FColor> colors; //���Կ�
	colorBuffer.GetVertexColors(colors);//����ü�÷������� ������������
	if (colors.Num() < 1)
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor::White);//�÷�������׳ɾ��� �������������ĥ�ϱ�

	}

	//file Archive 
	FVertexData data;//����������籸��ü�����Һ���
	for (uint32 i = 0; i < vertexCount; i++)
	{
		//��ȸ�ϸ鼭�����¸�����������������ֱ�
		data.Positions.Add(positionBuffer.VertexPosition(i));//��ġ
		data.Normals.Add(metaBuffer.VertexTangentZ(i));//����
		data.UVs.Add(metaBuffer.GetVertexUV(i, 0));//�ؽ���
		data.Colors.Add(colors[i]);//��
	}

	TArray<uint32> indices; 
	indexBuffer.GetCopy(indices);//�ε������� ����
	data.Indices.Insert((int32*)indices.GetData(),indexCount,0);//�ε��������ֱ� �����ּ�,��������,���۹�ȣ = �ε���0������ �����������ֱ�

	FBufferArchive buffer; //�ޱ�(����)�� ����
	//buffer << data.Positions; //���ۿ� ��������������ġ�����ֱ�
	//buffer << data.Indices; //�ε��� �����ε��ؼ��ؿ����ξ�
	buffer << data; //���ۿ� ������(���籸��ü) ����

	//save file binary ���̳ʸ�������
	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);//����������� �ϴ°� �迭, �����������̸� ���������Ѱ����� �̾������ �������������
	buffer.FlushCache();//�����Ҷ� �ݱ⵵���� ���������������ϱ� ��ġ�°Ź����� ���۳����������
	buffer.Empty();//�����Ҷ� �ݱ�¾��� �ϴ������������Ͱ���

	FString str;
	str.Append(FPaths::GetCleanFilename(fileNames[0]));//�տ����丮������ �����̸������
	str.Append("binary file save");
	GLog->Log(str);//�α����

	//save file csv csv������
	FString planeText;//�Է¿� SaveStringToFile�� fstring���γ־ߵ�
	for (uint32 i = 0; i < vertexCount; i++)
	{
		planeText.Append(data.Positions[i].ToString() + ",");//����
		planeText.Append(data.Normals[i].ToString() + ",");//�븻+����
		planeText.Append(data.UVs[i].ToString() + "\n");//�ؽ��� +�ٹٲ�
	}

	
	FString planeTextPath = FPaths::GetBaseFilename(fileNames[0], false);//Ȯ���ں���Ǯ��� (������ bin�ٿ����Ȼ��� bin�ɼ�������)
	planeTextPath.Append(".csv"); //�׳ɵڿ��ȵ��ü����վ csv�ֱ�
	FFileHelper::SaveStringToFile(planeText,*planeTextPath); //csv������(��) �������ִ°�

	return FReply::Handled();
}
