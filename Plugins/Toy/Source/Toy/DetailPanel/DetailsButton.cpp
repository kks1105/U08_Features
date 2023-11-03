

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
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("AwesomeCategory");//기존에디터 카테고리가있으면 편집 없으면생성해줌

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
			.HAlign(HAlign_Fill) //todo 버튼클릭이벤트
			.OnClicked(this, &FDetailsButton::OnClicked_ShuffleMaterial)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Shuffle"))
			]
		];//내용추가하기+ 네임컨텐츠 추가 (디테일패널왼쪽) 텍스트이+벨류컨텐츠 추가(디테일패널오른쪽) .valign정렬,MaxDesiredWidth최대크기 버튼+텍스트 OnClicked딜리게이트 , 


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
			.HAlign(HAlign_Fill) //todo 버튼클릭이벤트
			.OnClicked(this, &FDetailsButton::OnClicked_SaveVertexData)
			.Content()
			[
				SNew(STextBlock)
				.Text(FText::FromString("Save to Binary File"))
			]
			];//내용추가하기+ 네임컨텐츠 추가 (디테일패널왼쪽) 텍스트이+벨류컨텐츠 추가(디테일패널오른쪽) .valign정렬,MaxDesiredWidth최대크기 버튼+텍스트 OnClicked딜리게이트 , 


		DetailBuilder.GetObjectsBeingCustomized(Objects);
}


FReply FDetailsButton::OnClicked_ShuffleMaterial()
{
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);//다이나믹 캐스트
	if (actor == nullptr)return FReply::Unhandled(); //엑터있으면 처리안된거알림리턴

	actor->ShuffleMaterial();  //머티리얼세팅한거 랜덤세팅하는거
	return FReply::Handled(); //처리됬다고알림리턴
}

FReply FDetailsButton::OnClicked_SaveVertexData()
{
	//load vertex data from Sm_Asset
	//get SM Asset
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);//다이나믹 캐스트
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());//가져오기
	UStaticMeshComponent* meshComp  = Cast<UStaticMeshComponent>(comp); //캐스트
	if (meshComp == nullptr) return FReply::Unhandled(); //캐스트실패시 언핸들 
	
	UStaticMesh* meshAsset = meshComp->GetStaticMesh();//메쉬컴프의 스태틱메쉬가져오기
	if (meshAsset == nullptr) return FReply::Unhandled();// 널체크 없으면 언핸들
	FStaticMeshRenderData* renderData = meshAsset->RenderData.Get(); // 렌더데이터가져오기
	if (renderData->LODResources.Num() < 1) return FReply::Unhandled(); //렌더널체크

	//GetVertexData
	FStaticMeshLODResources& lod = renderData->LODResources[0];//lod0번 =최대퀄리티 가장정점많은상태 용량커서레퍼런스로받음

	FPositionVertexBuffer& positionBuffer = lod.VertexBuffers.PositionVertexBuffer; //정점의위치정보가져오기ㄴ 용량커서레퍼런스로받음
	FStaticMeshVertexBuffer& metaBuffer = lod.VertexBuffers.StaticMeshVertexBuffer;//uv,normal,tanzent 텍스쳐 음영 그림자등등가져옴 용량커서레퍼런스로받음
	FColorVertexBuffer& colorBuffer = lod.VertexBuffers.ColorVertexBuffer; //정점의색정보
	FRawStaticIndexBuffer& indexBuffer = lod.IndexBuffer; //인덱스정보 = 겹치는정점 구조체순서처리해서 용량감소

	if(positionBuffer.GetNumVertices()<1) return FReply::Unhandled();//정점이없으면 끊키
	if (indexBuffer.GetNumIndices() < 1) return FReply::Unhandled();//인덱스없으면 끈키

	uint32 vertexCount = positionBuffer.GetNumVertices();//버텍스숫자가져옴
	int32 indexCount = indexBuffer.GetNumIndices(); //-가들어올수도있어서 인트로 인덱스숫자가져옴

	GLog->Logf(TEXT("Vertex Count : %d"), vertexCount);//버택스개수숫자나오게하기
	GLog->Logf(TEXT("Index Count : %d"), indexCount);//인덱스개수

	//Save File Dialog
	//On Save file dialog(windowAPI) 윈도우파일저장창열기
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle(); //윈도우창가져오는함수 에서 윈도우핸들가져오는함수

	FString path;//밑에넣을려고만듦
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	platform->SaveFileDialog(handle, "Save",path,"","Binary File(*.bin)|*.bin",EFileDialogFlags::None,fileNames);//파일저장방식(저장은따로만들어야됨) 윈도우핸들,이름,패스,디폴트파일,필터(파일형식확장자앞에있는거),플래그?,파일풀경로
	if(fileNames.Num()<1) return FReply::Unhandled();//저장없으면언핸들

	//GLog->Log(*fileNames[0]); //파일이름찍기

	TArray<FColor> colors; //기입용
	colorBuffer.GetVertexColors(colors);//구조체컬러버퍼의 정점색가져옴
	if (colors.Num() < 1)
	{
		for (uint32 i = 0; i < vertexCount; i++)
			colors.Add(FColor::White);//컬러있으면그냥쓰고 없으면흰색으로칠하기

	}

	//file Archive 
	FVertexData data;//헤더에서만든구조체저장할변수
	for (uint32 i = 0; i < vertexCount; i++)
	{
		//순회하면서가져온모든정점개수끝까지넣기
		data.Positions.Add(positionBuffer.VertexPosition(i));//위치
		data.Normals.Add(metaBuffer.VertexTangentZ(i));//음염
		data.UVs.Add(metaBuffer.GetVertexUV(i, 0));//텍스쳐
		data.Colors.Add(colors[i]);//색
	}

	TArray<uint32> indices; 
	indexBuffer.GetCopy(indices);//인덱스버퍼 복사
	data.Indices.Insert((int32*)indices.GetData(),indexCount,0);//인덱스정보넣기 시작주소,넣을숫자,시작번호 = 인덱스0번부터 마지막까지넣기

	FBufferArchive buffer; //받기(저장)용 버퍼
	//buffer << data.Positions; //버퍼에 데이터의정점위치정보넣기
	//buffer << data.Indices; //인덱스 오버로딩해서밑에껄로씀
	buffer << data; //버퍼에 데이터(만든구조체) 저장

	//save file binary 바이너리로저장
	FFileHelper::SaveArrayToFile(buffer, *fileNames[0]);//어래이파일저장 하는거 배열, 저장할파일이름 파일저장한곳에서 이어서저장함 덮어쓰기하지않음
	buffer.FlushCache();//삭제할때 닫기도해줌 위에서저장했으니까 겹치는거방지로 버퍼내용삭제해줌
	buffer.Empty();//삭제할때 닫기는안함 하는일은위에꺼와같음

	FString str;
	str.Append(FPaths::GetCleanFilename(fileNames[0]));//앞에디렉토리날리고 파일이름만출력
	str.Append("binary file save");
	GLog->Log(str);//로그찍기

	//save file csv csv로저장
	FString planeText;//입력용 SaveStringToFile은 fstring으로넣야됨
	for (uint32 i = 0; i < vertexCount; i++)
	{
		planeText.Append(data.Positions[i].ToString() + ",");//정점
		planeText.Append(data.Normals[i].ToString() + ",");//노말+띄어쓰기
		planeText.Append(data.UVs[i].ToString() + "\n");//텍스쳐 +줄바꿈
	}

	
	FString planeTextPath = FPaths::GetBaseFilename(fileNames[0], false);//확장자빠진풀경로 (위에서 bin붙여서안빼면 bin될수도있음)
	planeTextPath.Append(".csv"); //그냥뒤에안들어올수도잇어서 csv넣기
	FFileHelper::SaveStringToFile(planeText,*planeTextPath); //csv로저장(평문) 읽을수있는거

	return FReply::Handled();
}
