//
//  StateMachineModule.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "StateMachineModule.h"

#include "FieldState.h"

StateMachineModule* StateMachineModule::_instance;

void StateMachineModule::releaseStates()
{
    for (auto state : _state_hash) {
        delete state.second;
    }
    _state_hash.clear();
}

void StateMachineModule::registerState(std::string key, IState *state)
{
    _state_hash.insert(std::make_pair(key, state));
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