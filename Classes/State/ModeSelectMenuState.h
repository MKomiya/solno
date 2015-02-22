//
//  ModeSelectMenuState.h
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#ifndef __solno__ModeSelectMenuState__
#define __solno__ModeSelectMenuState__

#include <stdio.h>
#include "State.h"

class ModeSelectMenuLayer;
class ModeSelectMenuState : public Raciela::State
{
public:
    static ModeSelectMenuState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;
    
private:
    ModeSelectMenuLayer* view;
};

#endif /* defined(__solno__ModeSelectMenuState__) */
