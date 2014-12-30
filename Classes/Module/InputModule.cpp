//
//  InputModule.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "InputModule.h"

InputModule* InputModule::_instance;

void InputModule::setInputCommand(InputCommand command)
{
    CCLOG("InputModule: setInputCommand");
    now_command = command;
}

InputCommand InputModule::getInputCommand()
{
    CCLOG("InputModule: getInputCommand");
    return now_command;
}

void InputModule::setInputCommandByString(std::string command_str)
{
    InputCommand command;
    if (command_str == "up") {
        command = InputCommand::MOVE_UP;
    } else if (command_str == "left") {
        command = InputCommand::MOVE_LEFT;
    } else if (command_str == "right") {
        command = InputCommand::MOVE_RIGHT;
    } else if (command_str == "down") {
        command = InputCommand::MOVE_DOWN;
    } else {
        throw "Invalid command string";
    }
    
    setInputCommand(command);
}