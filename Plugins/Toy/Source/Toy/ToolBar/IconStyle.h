
#pragma once

#include "CoreMinimal.h"


class TOY_API IconStyle
{
public:
	static TSharedPtr<IconStyle> Get(); //����Ʈ ������ ���Ұ�
	static void Shutdown();// ���������Ʈ ���۷������ҽ�ų��

public:
	IconStyle();
	~IconStyle();

private:
	static TSharedPtr<IconStyle> Instance;

private:
	const FName StyleSetName = "ToyStyle"; //��Ÿ�Ͼտ������̸�
	TSharedPtr<class FSlateStyleSet> StyleSet;//��Ÿ�տ��ٴ°������Ұ�


};
