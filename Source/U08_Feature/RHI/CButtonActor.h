
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CButtonActor.generated.h"

UENUM(BlueprintType) //��Ƽ���� ���� ����4��
enum class EMaterialType : uint8
{
	Gold,Wood,Concrete,Brick,Max

};

USTRUCT(BlueprintType) //������������ ��Ƽ���� �ؽ���Ÿ�԰� �÷� �Ķ����Ÿ�Ե�
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
		class UStaticMeshComponent* Mesh; //�޽�
	
	UPROPERTY(VisibleDefaultsOnly)
		class UMaterialInstanceConstant* Material;//�����͹�ưŬ���ý����ҰŶ� �ܽ�Ʈ�κ���Ұ��ع���
	
	UPROPERTY(EditDefaultsOnly)
		FMaterialParameterData MaterialParameters[(int32)EMaterialType::Max];//��Ƽ���� �Ķ����
};
