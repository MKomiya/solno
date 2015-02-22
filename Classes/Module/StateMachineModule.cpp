//
//  StateMachineModule.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "StateMachineModule.h"

USING_NS_CC;

StateMachineModule* StateMachineModule::instance;

void StateMachineModule::release()
{
    _state_hash.clear();
    
    Ref::release();
}

void StateMachineModule::registerState(std::string key, Raciela::State *state)
{
    _state_hash.insert(key, state);
}

void StateMachineModule::changeState(std::string key)
{
    if (_state_hash.find(key) == _state_hash.end()) {
        throw "invalid state key";
    }
    
    if (current_state) current_state->exit();
    current_state = _state_hash.find(key)->second;
    current_state->enter();
}

Raciela::State* StateMachineModule::getState(std::string key)
{
    auto it = _state_hash.find(key);
    if (it == _state_hash.end()) {
        throw "invalid state key";
    }
    return it->second;
}

void StateMachineModule::update()
{
    current_state->update();
}