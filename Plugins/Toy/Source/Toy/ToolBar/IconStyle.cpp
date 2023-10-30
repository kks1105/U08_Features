

#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<IconStyle> IconStyle::Instance = nullptr;//���۷����ʱ�ȭ

TSharedPtr<IconStyle> IconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new IconStyle());//�ν��Ͻ������ø���




	return Instance;
}

void IconStyle::Shutdown()
{
	if (Instance.IsValid())//ī��Ʈ���̳ʽ��ƴϸ�
		Instance.Reset();//�ʱ�ȭ

}

IconStyle::IconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));//��Ÿ�ϼ¿ø���

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();//�÷����ΰ��������Լ� (�÷������̸�)
	path += "/Resources";//������ ���ҽ�����
	StyleSet->SetContentRoot(path);//��Ÿ�ϼ°������� �⺻��θ� ���ҽ������μ���

	FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48)); //��� �������� ������ png , ������ 48
	FString name = StyleSetName.ToString() + ".SpawnVertex"; //�̸�
	StyleSet->Set(FName(name), brush); //��Ÿ�ϼ�

	//FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //�������̸� SlateEditorStyle���ִ°Ű�����

}

IconStyle::~IconStyle()
{


}
