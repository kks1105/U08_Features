

#include "DetailsButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "RHI/CButtonActor.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
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
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);//다이나믹 캐스트
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());//가져오기
	UStaticMeshComponent* meshComp  = Cast<UStaticMeshComponent>(comp); //캐스트
	if (meshComp == nullptr) return FReply::Unhandled(); //캐스트실패시 언핸들 
	

	//Save File Dialog
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle(); //윈도우창가져오는함수 에서 윈도우핸들가져오는함수

	FString path;//밑에넣을려고만듦
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	platform->SaveFileDialog(handle, "Save",path,"","Binary File(*.bin)|*.bin",EFileDialogFlags::None,fileNames);//파일저장방식(저장은따로만들어야됨) 윈도우핸들,이름,패스,디폴트파일,필터(파일형식확장자앞에있는거),플래그?,파일풀경로
	if(fileNames.Num()<1) return FReply::Unhandled();//저장없으면언핸들

	GLog->Log(*fileNames[0]); //파일이름찍기

	return FReply::Handled();
}
