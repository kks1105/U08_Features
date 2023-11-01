
#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FCollectionData
{
	FString Name;//�̸�
	FVector Location;//��ġ
	FVector Forward;//����

};

class TOY_API FDebuggerCategory :  public FGameplayDebuggerCategory
{

public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance(); //�����ī�װ� ��Ͽ�

public:
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor); //�����ͼ����Լ�
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override; //�����ѵ����ͱ׸����Լ�

private:
	FCollectionData PlayerPawnData;//�÷��̾����
	FCollectionData ForwardActorData;//���浥����
	FCollectionData DebugActorData;//������� (�⺻������)������


};
