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

class IState;
class StateMachineModule
{
public:
    static StateMachineModule* getInstance() {
        if (!_instance) {
            _instance = new StateMachineModule();
        }
        return _instance;
    }
    
    void registerState(std::string key, IState* state);
    void setNowState(std::string key);
    void update();
    
private:
    static StateMachineModule* _instance;
    std::unordered_map<std::string, IState*> _state_hash;
    
    std::string _now_state;
};

#endif /* defined(__solno__StateMachineModule__) */
