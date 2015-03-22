//
//  Tree.h
//  solno
//
//  Created by S_Wyvern on 2015/02/26.
//
//

#ifndef __solno__Tree__
#define __solno__Tree__

#include <stdio.h>
#include "FieldObject.h"
#include "Direction.h"

class FieldLayer;
class FieldState;
class Tree : public FieldObject
{
public:
    Tree(FieldState* state, int id, cocos2d::ValueMap data);
    
    virtual void executeDecideAction() override;
    virtual bool isPassablePlayer() override;
    virtual int getBreakItemId() override;
};

#endif /* defined(__solno__Tree__) */
