

#include "IconStyle.h"
#include "Styling/SlateStyle.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FIconStyle> FIconStyle::Instance = nullptr;//레퍼런스초기화

TSharedPtr<FIconStyle> FIconStyle::Get()
{
	if (Instance == nullptr)
		Instance = MakeShareable(new FIconStyle());//인스턴스생성올리기




	return Instance;//첫번째에등록 두번째부터 이미등록된거올림
}

void FIconStyle::Shutdown()
{
	if (Instance.IsValid())//카운트마이너스아니면
		Instance.Reset();//초기화

}

FIconStyle::FIconStyle()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));//스타일셋올리기

	//D:\202304123DprojectK\U08_Features\Plugins\Toy\Resources 실제경로 밑에는 경로압축 
	FString path = IPluginManager::Get().FindPlugin("Toy")->GetBaseDir();//플러그인가져오는함수 (플러그인이름)
	path += "/Resources";//패스에 토이의 리소스폴더위치 더함
	StyleSet->SetContentRoot(path);//스타일셋가져오는 기본경로를 리소스폴더로설정


	RegisterIcon("SpawnVertex", path / "Icon.png", FVector2D(48), SpawnVertexButtonIcon); //아이콘등록(아이콘이름,경로스트링으로,사이즈,저장용FSlateIcon타입변수)
	RegisterIcon("OpenViewer", path / "Icon2.png", FVector2D(48), OpenViewerButtonIcon); //아이콘등록2(아이콘이름,경로스트링으로,사이즈,저장용FSlateIcon타입변수)
	//FSlateImageBrush* brush = new FSlateImageBrush(path / "Icon.png", FVector2D(48)); //경로 리스소의 아이콘 png , 사이즈 48
	//FString StyleName = StyleSetName.ToString() + ".SpawnVertex"; //이름
	//StyleSet->Set(FName(StyleName), brush); //스타일셋 키와벨류넣기 내부에서벨류안쓰면딜리트해줌

	////FSlateIcon icon = FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.SelectMode"); //아이콘이름 SlateEditorStyle에있는거가져옴
	//SpawnVertexButtonIcon = FSlateIcon(StyleSetName,FName(StyleName));//아이콘가져오기 위에 아이콘png

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());//스타일셋을 에디터레지스트리에등록 쉐어드포인터라 *겟

}

FIconStyle::~FIconStyle()
{
	if (StyleSet.IsValid() == false) return;//아무것도없으면

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSetName);//에디터레지스트리에서 해제
	StyleSet.Reset();//리셋

}

void FIconStyle::RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon)
{
	FSlateImageBrush* brush = new FSlateImageBrush(InPath,InSize); //경로 리스소의 아이콘 png , 사이즈 48
	FString StyleName = StyleSetName.ToString() + "." + InPostFix; //이름
	StyleSet->Set(FName(StyleName), brush); //스타일셋 키와벨류넣기 내부에서벨류안쓰면딜리트해줌

	
	OutSlateIcon = FSlateIcon(StyleSetName, FName(StyleName));//아이콘가져오기 위에 아이콘png

}
