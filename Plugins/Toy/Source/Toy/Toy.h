
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToyModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;//에디터킬때
	virtual void ShutdownModule() override;//끌때

private:
	TSharedPtr<FExtender> Extender; //FExtender* Extender 
	
private:
	void AddToolBar_SpawnVertex(class FToolBarBuilder& InToolBarBuilder);
	void AddToolBar_OpenViewer(class FToolBarBuilder& InToolBarBuilder);


};
