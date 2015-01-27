//
//  ItemMenuState.h
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#ifndef __solno__ItemMenuState__
#define __solno__ItemMenuState__

#include <stdio.h>
#include "StateBase.h"

class ItemMenuState : public StateBase
{
public:
    static ItemMenuState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
};

#endif /* defined(__solno__ItemMenuState__) */
