
#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class TOY_API FButtonCommand : public TCommands<FButtonCommand>
{
public:
	FButtonCommand();
	~FButtonCommand();

public:
	virtual void RegisterCommands() override;//�θ𰡻��Լ������� ��ɵ�������Ʈ���� �������Ͷ���Լ��ȿ�����

private:
	void SpawnVertexButton_Pressed();//��ư�������� �׼�

public:
	TSharedPtr<FUICommandInfo> SpawnVertexButton;//uicommand ��ư��ü�������ġ
	TSharedPtr<FUICommandList> SpawnVertexCommand;//��ư�׼ǽ��೻��


};
