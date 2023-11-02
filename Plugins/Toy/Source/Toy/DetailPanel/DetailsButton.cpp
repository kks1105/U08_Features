

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
	ACButtonActor* actor = Cast<ACButtonActor>(Objects[0]);//���̳��� ĳ��Ʈ
	UActorComponent* comp = actor->GetComponentByClass(UStaticMeshComponent::StaticClass());//��������
	UStaticMeshComponent* meshComp  = Cast<UStaticMeshComponent>(comp); //ĳ��Ʈ
	if (meshComp == nullptr) return FReply::Unhandled(); //ĳ��Ʈ���н� ���ڵ� 
	

	//Save File Dialog
	IMainFrameModule& mainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
	void* handle = mainFrame.GetParentWindow()->GetNativeWindow()->GetOSWindowHandle(); //������â���������Լ� ���� �������ڵ鰡�������Լ�

	FString path;//�ؿ�����������
	TArray<FString> fileNames;
	IDesktopPlatform* platform = FDesktopPlatformModule::Get();

	platform->SaveFileDialog(handle, "Save",path,"","Binary File(*.bin)|*.bin",EFileDialogFlags::None,fileNames);//����������(���������θ����ߵ�) �������ڵ�,�̸�,�н�,����Ʈ����,����(��������Ȯ���ھտ��ִ°�),�÷���?,����Ǯ���
	if(fileNames.Num()<1) return FReply::Unhandled();//�����������ڵ�

	GLog->Log(*fileNames[0]); //�����̸����

	return FReply::Handled();
}
