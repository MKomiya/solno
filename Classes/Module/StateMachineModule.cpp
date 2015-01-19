//
//  StateMachineModule.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "StateMachineModule.h"

USING_NS_CC;

StateMachineModule* StateMachineModule::_instance;

void StateMachineModule::release()
{
    _state_hash.clear();
    
    Ref::release();
}

void StateMachineModule::registerState(std::string key, StateBase *state)
{
    _state_hash.insert(key, state);
}

void StateMachineModule::setNowState(std::string key)
{
    if (_state_hash.find(key) == _state_hash.end()) {
        throw "invalid state key";
    }
    _now_state = key;
}

void StateMachineModule::update()
{
    auto it = _state_hash.find(_now_state);
    auto state = it->second;
    state->update();
}