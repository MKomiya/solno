//
//  MakeMenuState.h
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#ifndef __solno__MakeMenuState__
#define __solno__MakeMenuState__

#include <iostream>
#include "StateBase.h"

class MakeMenuState : public StateBase
{
public:
    static MakeMenuState* create();
    
    virtual void enter(int gate) override;
    virtual void update() override;
    virtual void exit() override;
};

#endif /* defined(__solno__MakeMenuState__) */
