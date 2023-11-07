
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"


class TOY_API FMeshViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);//누를때마다실행할함수
	static void Shutdown();//닫으면리셋하는역할

private:
	void OpenWindow_Internal(UObject* InAsset);//위에와세트

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);//RegisterTabSpawners에서 탭아이디로하는 딜리게이트

public:
	virtual FName GetToolkitFName() const override; //순수가상 오버라이드
	virtual FText GetBaseToolkitName() const override;//순수가상 오버라이드
	virtual FString GetWorldCentricTabPrefix() const override;//순수가상 오버라이드
	virtual FLinearColor GetWorldCentricTabColorScale(void) const override;//순수가상 오버라이드

private:
	static TSharedPtr<FMeshViewer> Instance;
	
};
