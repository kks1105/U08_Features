
#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;//부모가상함수재정의 명령딜리게이트관련 레지스터라는함수안에있음

private:
	void SpawnVertexButton_Pressed();//버튼눌렀을때 액션

public:
	TSharedPtr<FUICommandInfo> SpawnVertexButton;//uicommand 버튼객체저장될위치
	TSharedPtr<FUICommandList> SpawnVertexCommand;//버튼액션실행내용


};
