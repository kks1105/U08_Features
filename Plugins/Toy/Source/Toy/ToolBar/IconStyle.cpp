

#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyle> FIconStyle::Instance = nullptr;//���۷����ʱ�ȭ

TSharedPtr<FIconStyle> FIconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyle());//�ν��Ͻ������ø���




	return Instance;//ù��°����� �ι�°���� �̵̹�ϵȰſø�
}

void FIconStyle::Shutdown()
{
	if (Instance.IsValid())//ī��Ʈ���̳ʽ��ƴϸ�
		Instance.Reset();//�ʱ�ȭ

}

FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));//��Ÿ�ϼ¿ø���

	//D:\202304123DprojectK\U08_Features\Plugins\Toy\Resources ������� �ؿ��� ��ξ��� 
	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();//�÷����ΰ��������Լ� (�÷������̸�)
	path += "/Resources";//�н��� ������ ���ҽ�������ġ ����
	StyleSet->SetContentRoot(path);//��Ÿ�ϼ°������� �⺻��θ� ���ҽ������μ���


	RegisterIcon("SpawnVertex", path / "Icon.png", FVector2D(48), SpawnVertexButtonIcon); //�����ܵ��(�������̸�,��ν�Ʈ������,������,�����FSlateIconŸ�Ժ���)
	RegisterIcon("OpenViewer", path / "Icon2.png", FVector2D(48), OpenViewerButtonIcon); //�����ܵ��2(�������̸�,��ν�Ʈ������,������,�����FSlateIconŸ�Ժ���)
	//FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48)); //��� �������� ������ png , ������ 48
	//FString StyleName = StyleSetName.ToString() + ".SpawnVertex"; //�̸�
	//StyleSet->Set(FName(StyleName), brush); //��Ÿ�ϼ� Ű�ͺ����ֱ� ���ο��������Ⱦ������Ʈ����

	////FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //�������̸� SlateEditorStyle���ִ°Ű�����
	//SpawnVertexButtonIcon = FSlateIcon(StyleSetName,FName(StyleName));//�����ܰ������� ���� ������png

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());//��Ÿ�ϼ��� �����ͷ�����Ʈ������� ����������Ͷ� *��

}

FIconStyle::~FIconStyle()
{
	if (StyleSet.IsValid() == false) return;//�ƹ��͵�������

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);//�����ͷ�����Ʈ������ ����
	StyleSet.Reset();//����

}

void FIconStyle::RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath,InSize); //��� �������� ������ png , ������ 48
	FString StyleName = StyleSetName.ToString() + "." + InPostFix; //�̸�
	StyleSet->Set(FName(StyleName), brush); //��Ÿ�ϼ� Ű�ͺ����ֱ� ���ο��������Ⱦ������Ʈ����

	
	OutSlateIcon = FSlateIcon(StyleSetName, FName(StyleName));//�����ܰ������� ���� ������png

}
