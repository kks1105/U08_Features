
#pragma once

#include "CoreMinimal.h"


class TOY_API FIconStyle
{
public:
	static TSharedPtr<FIconStyle> Get(); //����Ʈ ������ ���Ұ�
	static void Shutdown();// ���������Ʈ ���۷������ҽ�ų��

public:
	FIconStyle();
	~FIconStyle();

private:
	void RegisterIcon(const FString& InPostFix, const FString& InPath, const FVector2D& InSize, FSlateIcon& OutSlateIcon);//�����ܵ�� �Լ�(�������̸�,��ν�Ʈ������,������,�����FSlateIconŸ�Ժ���)

private:
	static TSharedPtr<FIconStyle> Instance;

private:
	const FName StyleSetName = "ToyStyle"; //��Ÿ�Ͼտ������̸�
	TSharedPtr<class FSlateStyleSet> StyleSet;//��Ÿ�տ��ٴ°������Ұ�

public:
	FSlateIcon SpawnVertexButtonIcon; //FSlateIcon �����
	FSlateIcon OpenViewerButtonIcon; //���º�� FSlateIcon �����



};
