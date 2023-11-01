
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CButtonActor.generated.h"

UCLASS()
class U08_FEATURE_API ACButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ACButtonActor();

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh; //메쉬
	
	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;//에디터버튼클릭시실행할거라 콘스트로변경불가해버림
	
};
