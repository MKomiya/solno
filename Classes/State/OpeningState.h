//
//  OpeningState.h
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#ifndef __solno__OpeningState__
#define __solno__OpeningState__

#include <stdio.h>
#include <cocos2d.h>
#include "State.h"

class OpeningLayer;
class OpeningState : public Raciela::State
{
public:
    static OpeningState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;

    CC_SYNTHESIZE(OpeningLayer*, view, View);
};

#endif /* defined(__solno__OpeningState__) */
