

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
	IDetailCategoryBuilder& category = DetailBuilder.EditCategory("AwesomeCategory");//기존에디터 카테고리가있으면 편집 없으면생성해줌

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
			.HAlign(HAlign_Fill) //todo 버튼클릭이벤트
			[
				SNew(STextBlock)
				.Text(FText::FromString("Shuffle"))
			]
		];//내용추가하기+ 네임컨텐츠 추가 (디테일패널왼쪽) 텍스트이+벨류컨텐츠 추가(디테일패널오른쪽) .valign정렬,MaxDesiredWidth최대크기 버튼+텍스트

}
