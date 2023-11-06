
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CDetailAsset.generated.h"


UCLASS()
class U08_FEATURE_API UCDetailAsset : public UObject
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
		FVector Location;//디테일패널에서보일변수

};
