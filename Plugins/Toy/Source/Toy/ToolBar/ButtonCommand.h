
#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;//�θ𰡻��Լ������� ��ɵ�������Ʈ����

public:
	TSharedPtr<FUICommandInfo> CommandInfo;//uicommand ��ư��ü�������ġ


};
