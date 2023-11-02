
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CButtonActor.generated.h"

UENUM(BlueprintType) //머티리얼 종류 아직4개
enum class EMaterialType : uint8
{
	Gold,Wood,Concrete,Brick,Max

};

USTRUCT(BlueprintType) //블프에서보일 머티리얼 텍스쳐타입과 플룻 파라미터타입들
struct FMaterialParameterData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		class UTexture* BaseMap;

	UPROPERTY(EditAnywhere)
		class UTexture* NormalMap;

	UPROPERTY(EditAnywhere)
		class UTexture* RoughnessMap;

	UPROPERTY(EditAnywhere)
		float Metalic;

	UPROPERTY(EditAnywhere)
		float Roughness_Min;

	UPROPERTY(EditAnywhere)
		float Roughness_Max;

};

UCLASS()
class U08_FEATURE_API ACButtonActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ACButtonActor();

protected:
	virtual void BeginPlay() override;

#if WITH_EDITOR
public:
	void ShuffleMaterial();
#endif

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh; //메쉬
	
	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;//에디터버튼클릭시실행할거라 콘스트로변경불가해버림
	
	UPROPERTY(EditDefaultsOnly)
		FMaterialParameterData MaterialParameters[(int32)EMaterialType::Max];//머티리얼 파라미터
};
