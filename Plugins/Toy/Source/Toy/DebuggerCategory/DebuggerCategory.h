
#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"

struct FCollectionData
{
	FString Name;//이름
	FVector Location;//위치
	FVector Forward;//전방

};

class TOY_API FDebuggerCategory :  public FGameplayDebuggerCategory
{

public:
	FDebuggerCategory();
	~FDebuggerCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance(); //디버그카테고리 등록용

public:
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor); //데이터수집함수
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override; //수집한데이터그리는함수

private:
	FCollectionData PlayerPawnData;//플레이어데이터
	FCollectionData ForwardActorData;//전방데이터
	FCollectionData DebugActorData;//디벅엑터 (기본으론적)데이터


};
