

#include "ButtonCommand.h"

FButtonCommand::FButtonCommand():TCommands("ContextName",FText::FromString("ContextDesc"),NAME_None,FEditorStyle::GetStyleSetName())
{


}

FButtonCommand::~FButtonCommand() : TCommands
{


}

void FButtonCommand::RegisterCommands()
{
//#define

//	UI_COMMAND(CommandInfo,"LoadMesh","Load Mesh Data",EUserInterfaceActionType::Button,FInputChord());//저장위치,?,?,인터페이스타입,?
//undef
}
