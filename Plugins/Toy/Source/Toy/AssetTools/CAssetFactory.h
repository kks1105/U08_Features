
#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CAssetFactory.generated.h"


UCLASS()
class TOY_API UCAssetFactory : public UFactory
{
	GENERATED_BODY()
	
private:
	UCAssetFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;//우클릭시 뭐나올때호출됨



};
