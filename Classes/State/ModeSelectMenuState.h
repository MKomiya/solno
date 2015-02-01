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
#include "MenuState.h"

class ModeSelectMenuLayer;
class ModeSelectMenuState : public MenuState
{
public:
    static ModeSelectMenuState* create();
    
    virtual void enter(int gate) override;
    virtual void update() override;
    virtual void exit() override;
    
private:
    ModeSelectMenuLayer* view;
};

#endif /* defined(__solno__ModeSelectMenuState__) */
