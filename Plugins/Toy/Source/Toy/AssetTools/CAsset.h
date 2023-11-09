
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAsset.generated.h"


UCLASS()
class TOY_API UCAsset : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE FName GetName() { return Name; }//关俊波百
	FORCEINLINE class UStaticMesh* GetShape() { return Shape; }//关俊波百
	FORCEINLINE float GetDropRate() { return DropRate; }//关俊波百


protected:
	UPROPERTY(EditAnywhere)
		FName Name;//焊老芭

	UPROPERTY(EditAnywhere)
		class UStaticMesh* Shape;//焊老芭

	UPROPERTY(EditAnywhere)
		float DropRate;//焊老芭
	


};
