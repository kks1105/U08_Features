
#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;//부모가상함수재정의 명령딜리게이트관련

public:
	TSharedPtr<FUICommandInfo> CommandInfo;//uicommand 버튼객체저장될위치


};
