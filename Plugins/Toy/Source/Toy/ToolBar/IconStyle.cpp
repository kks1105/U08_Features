

#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<IconStyle> IconStyle::Instance = nullptr;//레퍼런스초기화

TSharedPtr<IconStyle> IconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new IconStyle());//인스턴스생성올리기




	return Instance;
}

void IconStyle::Shutdown()
{
	if (Instance.IsValid())//카운트마이너스아니면
		Instance.Reset();//초기화

}

IconStyle::IconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));//스타일셋올리기

	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();//플러그인가져오는함수 (플러그인이름)
	path += "/Resources";//토이의 리소스폴더
	StyleSet->SetContentRoot(path);//스타일셋가져오는 기본경로를 리소스폴더로설정

	FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48)); //경로 리스소의 아이콘 png , 사이즈 48
	FString name = StyleSetName.ToString() + ".SpawnVertex"; //이름
	StyleSet->Set(FName(name), brush); //스타일셋

	//FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //아이콘이름 SlateEditorStyle에있는거가져옴

}

IconStyle::~IconStyle()
{


}
