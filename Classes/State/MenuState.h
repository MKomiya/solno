//
//  MenuState.h
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#ifndef __solno__MenuState__
#define __solno__MenuState__

#include <stdio.h>
#include "StateBase.h"

class MenuState : public StateBase
{
public:
    virtual void enter(int gate) override;
    virtual void update() override;
    virtual void exit() override;
};


#endif /* defined(__solno__MenuState__) */
