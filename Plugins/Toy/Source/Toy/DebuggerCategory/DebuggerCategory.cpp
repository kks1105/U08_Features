

#include "DebuggerCategory.h"
#include "CanvasItem.h"

FDebuggerCategory::FDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;//����׿��Ͱ���� ����׿������԰��� ����Ǯ�� ������ ���ǿ��͸� ����׿��ͷ� �������Ҽ�����

}

FDebuggerCategory::~FDebuggerCategory()
{
}

TSharedRef<FGameplayDebuggerCategory> FDebuggerCategory::MakeInstance()
{


	return MakeShareable(new FDebuggerCategory()); 
}

void FDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor); //������

	APawn* playerPawn = OwnerPC->GetPawn(); //����������������

	//player
	{
		PlayerPawnData.Name = playerPawn->GetName(); //�÷��̾��̸���������
		PlayerPawnData.Location = playerPawn->GetActorLocation();//�÷��̾���ġ��������
		PlayerPawnData.Forward = playerPawn->GetActorForwardVector(); //�÷��̾����溤�Ͱ�������

	}

	//ForwardActor
	{
		FHitResult hitResult; //��Ʈ����Ʈ
		FVector start = PlayerPawnData.Location;//������ �÷��̾���ġ
		FVector end = start + PlayerPawnData.Forward * 1e+4f;//���� ������+������+1��

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(playerPawn); //�÷��̾�������

		playerPawn->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, queryParams);//�þ߿����̴���ġ���� ��Ʈ����Ʈ,��ŸƮ��,����, �ݸ������̱⿩��,ó��


			if (hitResult.bBlockingHit) 
			{
				//���Ϳ��θ�ħ
				ForwardActorData.Name = hitResult.GetActor()->GetName(); //�θ�ģ�����̸���������
				ForwardActorData.Location = hitResult.GetActor()->GetActorLocation(); //��ġ��������
				ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector(); //�����庤�Ͱ�������
			}
			else
			{
				//���Ϳ��Ⱥθ�ħ
				ForwardActorData.Name = "No Tranced Forward Actor"; 
				ForwardActorData.Location = FVector::ZeroVector;
				ForwardActorData.Forward = FVector::ZeroVector;

			}


	}

	//DebugActor
	{
		if (!!DebugActor)
		{
			//����׿���������
			DebugActorData.Name = DebugActor->GetName(); //�̸���������
			DebugActorData.Location = DebugActor->GetActorLocation(); //������ġ��������
			DebugActorData.Forward = DebugActor->GetActorForwardVector(); //�������溤�Ͱ�������
		}
		else
		{

			//������
			DebugActorData.Name = "No DebugActor"; 
			DebugActorData.Location = FVector::ZeroVector;
			DebugActorData.Forward = FVector::ZeroVector;
		}


	}



}

void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);


	FCanvasTileItem item(FVector2D(10,10),FVector2D(300,230),FLinearColor(0,0,0,0.5f) );//�׸��� ��ġ,ũ��,��
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend; //���ĺ���
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);//�׸��¹�� �߰��Ҿ�����,x��ġ,y��ġ

	CanvasContext.Printf(FColor::Green, L"--player pawn");//�׳ɽ��۱�
	CanvasContext.Printf(FColor::White, L"Name: &s",*PlayerPawnData.Name);//�÷��̾��̸�
	CanvasContext.Printf(FColor::White, L"Location : %s", *PlayerPawnData.Location.ToString()); //�÷��̾���ġ
	CanvasContext.Printf(FColor::White, L"Forward : %s", *PlayerPawnData.Forward.ToString()); //�÷��̾����溤��
	CanvasContext.Printf(FColor::White, L"");//����

	CanvasContext.Printf(FColor::Green, L" -- Forward Actor --");//�����忢��
	CanvasContext.Printf(FColor::White, L"Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L" -- DebugActor Actor --");//����׿���
	CanvasContext.Printf(FColor::White, L"Name : %s", *DebugActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *DebugActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *DebugActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");



}
