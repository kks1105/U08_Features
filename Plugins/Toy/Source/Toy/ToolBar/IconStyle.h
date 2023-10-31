
#pragma once

#include "CoreMinimal.h"


class TOY_API FIconStyle
{
public:
	static TSharedPtr<FIconStyle> Get(); //포인트 생성과 겟할거
	static void Shutdown();// 쉐어드포인트 레퍼런스감소시킬거

public:
	FIconStyle();
	~FIconStyle();

private:
	void RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon);//아이콘등록 함수(아이콘이름,경로스트링으로,사이즈,저장용FSlateIcon타입변수)

private:
	static TSharedPtr<FIconStyle> Instance;

private:
	const FName StyleSetName = "ToyStyle"; //스타일앞에붙을이름
	TSharedPtr<class FSlateStyleSet> StyleSet;//스타앞에붙는거저장할거

public:
	FSlateIcon SpawnVertexButtonIcon; //FSlateIcon 저장용
	FSlateIcon OpenViewerButtonIcon; //오픈뷰어 FSlateIcon 저장용



};
