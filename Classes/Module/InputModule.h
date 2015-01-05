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

enum InputEvent {
    PRESS_UP, PRESS_RIGHT, PRESS_DOWN, PRESS_LEFT,
    RELEASE_UP, RELEASE_RIGHT, RELEASE_DOWN, RELEASE_LEFT
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
    
    void pushEvent(InputEvent e);
    InputEvent popEvent();
    
private:
    static InputModule* _instance;
    std::stack<InputEvent> _event_stack;
};

#endif /* defined(__solno__InputModule__) */
