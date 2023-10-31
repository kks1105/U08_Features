
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToyModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;//������ų��
	virtual void ShutdownModule() override;//����

private:
	TSharedPtr<FExtender> Extender; //FExtender* Extender 
	
private:
	void AddToolBar_SpawnVertex(class FToolBarBuilder& InToolBarBuilder);
	void AddToolBar_OpenViewer(class FToolBarBuilder& InToolBarBuilder);


};
