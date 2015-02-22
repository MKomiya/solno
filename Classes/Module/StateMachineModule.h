//
//  StateMachineModule.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__StateMachineModule__
#define __solno__StateMachineModule__

#include <stdio.h>
#include <unordered_map>
#include <dispatch/dispatch.h>
#include <cocos2d.h>
#include "State.h"

class StateMachineModule : cocos2d::Ref
{
public:
    static StateMachineModule* getInstance() {
        static dispatch_once_t token;
        dispatch_once(&token, ^{
            if (!instance) {
                instance = new StateMachineModule();
                instance->current_state = nullptr;
            }
        });
        return instance;
    }

    virtual void release();
    void registerState(std::string key, Raciela::State* state);
    void changeState(std::string key);
    Raciela::State* getState(std::string key);
    void update();
    
private:
    static StateMachineModule* instance;
    
    cocos2d::Map<std::string, Raciela::State*> _state_hash;
    Raciela::State* current_state;
};

#endif /* defined(__solno__StateMachineModule__) */
