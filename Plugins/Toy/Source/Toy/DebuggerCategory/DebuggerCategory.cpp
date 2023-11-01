

#include "DebuggerCategory.h"
#include "CanvasItem.h"

FDebuggerCategory::FDebuggerCategory()
{
	bShowOnlyWithDebugActor = false;//디버그엑터가없어도 디버그엑터진입가능 빙의풀고 월드의 임의엑터를 디버그엑터로 들어오게할수있음

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
	FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor); //슈퍼콜

	APawn* playerPawn = OwnerPC->GetPawn(); //오너의폰가져오기

	//player
	{
		PlayerPawnData.Name = playerPawn->GetName(); //플레이어이름가져오기
		PlayerPawnData.Location = playerPawn->GetActorLocation();//플레이어위치가져오기
		PlayerPawnData.Forward = playerPawn->GetActorForwardVector(); //플레이어전방벡터가져오기

	}

	//ForwardActor
	{
		FHitResult hitResult; //히트리졀트
		FVector start = PlayerPawnData.Location;//시작점 플레이어위치
		FVector end = start + PlayerPawnData.Forward * 1e+4f;//끝점 시작점+포워드+1만

		FCollisionQueryParams queryParams;
		queryParams.AddIgnoredActor(playerPawn); //플레이어폰제외

		playerPawn->GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, queryParams);//시야에보이는위치까지 히트리졀트,스타트점,끝점, 콜리젼보이기여부,처리


			if (hitResult.bBlockingHit) 
			{
				//엑터에부리침
				ForwardActorData.Name = hitResult.GetActor()->GetName(); //부리친엑터이름가져오기
				ForwardActorData.Location = hitResult.GetActor()->GetActorLocation(); //위치가져오기
				ForwardActorData.Forward = hitResult.GetActor()->GetActorForwardVector(); //포워드벡터가져오기
			}
			else
			{
				//엑터에안부리침
				ForwardActorData.Name = "No Tranced Forward Actor"; 
				ForwardActorData.Location = FVector::ZeroVector;
				ForwardActorData.Forward = FVector::ZeroVector;

			}


	}

	//DebugActor
	{
		if (!!DebugActor)
		{
			//디버그엑터잇으면
			DebugActorData.Name = DebugActor->GetName(); //이름가져오기
			DebugActorData.Location = DebugActor->GetActorLocation(); //엑터위치가져오기
			DebugActorData.Forward = DebugActor->GetActorForwardVector(); //엑터전방벡터가져오기
		}
		else
		{

			//없으면
			DebugActorData.Name = "No DebugActor"; 
			DebugActorData.Location = FVector::ZeroVector;
			DebugActorData.Forward = FVector::ZeroVector;
		}


	}



}

void FDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);


	FCanvasTileItem item(FVector2D(10,10),FVector2D(300,230),FLinearColor(0,0,0,0.5f) );//그리기 위치,크기,색
	item.BlendMode = ESimpleElementBlendMode::SE_BLEND_AlphaBlend; //알파블렌드
	CanvasContext.DrawItem(item, CanvasContext.CursorX, CanvasContext.CursorY);//그리는방법 추가할아이템,x위치,y위치

	CanvasContext.Printf(FColor::Green, L"--player pawn");//그냥시작글
	CanvasContext.Printf(FColor::White, L"Name: &s",*PlayerPawnData.Name);//플레이어이름
	CanvasContext.Printf(FColor::White, L"Location : %s", *PlayerPawnData.Location.ToString()); //플레이어위치
	CanvasContext.Printf(FColor::White, L"Forward : %s", *PlayerPawnData.Forward.ToString()); //플레이어전방벡터
	CanvasContext.Printf(FColor::White, L"");//공백

	CanvasContext.Printf(FColor::Green, L" -- Forward Actor --");//포워드엑터
	CanvasContext.Printf(FColor::White, L"Name : %s", *ForwardActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *ForwardActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *ForwardActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");

	CanvasContext.Printf(FColor::Green, L" -- DebugActor Actor --");//디버그엑터
	CanvasContext.Printf(FColor::White, L"Name : %s", *DebugActorData.Name);
	CanvasContext.Printf(FColor::White, L"Location : %s", *DebugActorData.Location.ToString());
	CanvasContext.Printf(FColor::White, L"Forward : %s", *DebugActorData.Forward.ToString());
	CanvasContext.Printf(FColor::White, L"");



}
