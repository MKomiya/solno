//
//  InputModule.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "InputModule.h"

InputModule* InputModule::_instance;

void InputModule::pushEvent(InputEvent e)
{
    _event_stack.push(e);
}

InputEvent InputModule::popEvent()
{
    if (_event_stack.empty()) {
        return InputEvent::NOTHING;
    }
    
    auto ret = _event_stack.top();
    _event_stack.pop();
    return ret;
}

void InputModule::pushParam(int params)
{
    _param_stack.push(params);
}

int InputModule::popParam()
{
    if (_param_stack.empty()) {
        return 0;
    }
    
    auto ret = _param_stack.top();
    _param_stack.pop();
    return ret;
}