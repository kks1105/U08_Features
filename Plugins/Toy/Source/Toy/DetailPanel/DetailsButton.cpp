

#include "DetailsButton.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

TSharedRef<class IDetailCustomization> FDetailsButton::MakeInstance()
{


	return MakeShareable(new FDetailsButton());
}

void FDetailsButton::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("AwesomeCategory");//���������� ī�װ��������� ���� �������������

	category.AddCustomRow(FText::FromString("Awesome")).
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
			[
				SNew(STextBlock)
				.Text(FText::FromString("Shuffle"))
			]
		];//�����߰��ϱ�+ ���������� �߰� (�������гο���) �ؽ�Ʈ��+���������� �߰�(�������гο�����) .valign����,MaxDesiredWidth�ִ�ũ�� ��ư+�ؽ�Ʈ

}
