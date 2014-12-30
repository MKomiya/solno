//
//  InputModule.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__InputModule__
#define __solno__InputModule__

#include <stdio.h>

enum InputCommand {
    NOTHING,
    MOVE_UP, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT,
    DECIDE, CANCELL
};

class InputModule
{
public:
    static InputModule* getInstance() {
        if (!_instance) {
            _instance = new InputModule();
        }
        return _instance;
    }
    
    void setInputCommand(InputCommand command);
    void setInputCommandByString(std::string command_str);
    InputCommand getInputCommand();
    
private:
    static InputModule* _instance;
    
    InputCommand now_command;
};

#endif /* defined(__solno__InputModule__) */
