//
//  StateMachineModule.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "StateMachineModule.h"
#include "IState.h"

StateMachineModule* StateMachineModule::_instance;

void StateMachineModule::registerState(std::string key, IState *state)
{
    CCLOG("StateMachineModule: registerState");
    _state_hash.insert(std::make_pair(key, state));
}

void StateMachineModule::setNowState(std::string key)
{
    CCLOG("StateMachineModule: setNowState");
    
    if (_state_hash.find(key) == _state_hash.end()) {
        throw "invalid state key";
    }
    _now_state = key;
}

void StateMachineModule::update()
{
    CCLOG("StateMachineModule: update");
    
    auto it = _state_hash.find(_now_state);
    auto state = it->second;
    state->update();
}