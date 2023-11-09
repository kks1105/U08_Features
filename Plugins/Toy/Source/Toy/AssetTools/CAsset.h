
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CAsset.generated.h"


UCLASS()
class TOY_API UCAsset : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE FName GetName() { return Name; }//�ؿ�����
	FORCEINLINE class UStaticMesh* GetShape() { return Shape; }//�ؿ�����
	FORCEINLINE float GetDropRate() { return DropRate; }//�ؿ�����


protected:
	UPROPERTY(EditAnywhere)
		FName Name;//���ϰ�

	UPROPERTY(EditAnywhere)
		class UStaticMesh* Shape;//���ϰ�

	UPROPERTY(EditAnywhere)
		float DropRate;//���ϰ�
	


};
