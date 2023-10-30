
#pragma once

#include "CoreMinimal.h"


class TOY_API IconStyle
{
public:
	static TSharedPtr<IconStyle> Get(); //포인트 생성과 겟할거
	static void Shutdown();// 쉐어드포인트 레퍼런스감소시킬거

public:
	IconStyle();
	~IconStyle();

private:
	static TSharedPtr<IconStyle> Instance;

private:
	const FName StyleSetName = "ToyStyle"; //스타일앞에붙을이름
	TSharedPtr<class FSlateStyleSet> StyleSet;//스타앞에붙는거저장할거


};
