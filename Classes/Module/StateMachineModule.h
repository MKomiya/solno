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

#include <StateBase.h>

class StateMachineModule : cocos2d::Ref
{
public:
    static StateMachineModule* getInstance() {
        static dispatch_once_t token;
        dispatch_once(&token, ^{
            if (!_instance) {
                _instance = new StateMachineModule();
            }
        });
        return _instance;
    }

    virtual void release();
    void registerState(std::string key, StateBase* state);
    void setNowState(std::string key);
    void update();
    
private:
    static StateMachineModule* _instance;
    cocos2d::Map<std::string, StateBase*> _state_hash;
    
    std::string _now_state;
};

#endif /* defined(__solno__StateMachineModule__) */
