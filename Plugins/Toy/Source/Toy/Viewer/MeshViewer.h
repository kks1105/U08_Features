
#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"


class TOY_API FMeshViewer : public FAssetEditorToolkit
{
public:
	static void OpenWindow(UObject* InAsset);//���������ٽ������Լ�
	static void Shutdown();//�����鸮���ϴ¿���

private:
	void OpenWindow_Internal(UObject* InAsset);//�����ͼ�Ʈ

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

private:
	TSharedRef<SDockTab> Spawn_ViewportTab(const FSpawnTabArgs& InArgs);//RegisterTabSpawners���� �Ǿ��̵���ϴ� ��������Ʈ

public:
	virtual FName GetToolkitFName() const override; //�������� �������̵�
	virtual FText GetBaseToolkitName() const override;//�������� �������̵�
	virtual FString GetWorldCentricTabPrefix() const override;//�������� �������̵�
	virtual FLinearColor GetWorldCentricTabColorScale(void) const override;//�������� �������̵�

private:
	static TSharedPtr<FMeshViewer> Instance;
	
};
