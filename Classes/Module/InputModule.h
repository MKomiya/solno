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
    NOTHING = 0,
    
    /* Controller Layer */
    PRESS_UP, PRESS_RIGHT, PRESS_DOWN, PRESS_LEFT,
    RELEASE_UP, RELEASE_RIGHT, RELEASE_DOWN, RELEASE_LEFT,
    PRESS_DECIDE, RELEASE_DECIDE,
    
    /* ModeSelectMenu Layer */
    PRESS_MODE_SELECT_ITEM, PRESS_MODE_SELECT_MAKE,
    
    /* ItemMenu Layer */
    PRESS_ITEM_SELECT,
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
    void pushParam(int params);
    InputEvent popEvent();
    int popParam();
    
private:
    static InputModule* _instance;
    std::stack<InputEvent> _event_stack;
    std::stack<int> _param_stack;
};

#endif /* defined(__solno__InputModule__) */
