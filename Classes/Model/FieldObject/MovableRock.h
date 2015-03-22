//
//  MovableRock.h
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#ifndef __solno__MovableRock__
#define __solno__MovableRock__

#include <stdio.h>
#include "FieldObject.h"
#include "Direction.h"

class FieldLayer;
class FieldState;
class MovableRock : public FieldObject
{
public:
    MovableRock(FieldState* state, int id, cocos2d::ValueMap data);
    
    virtual void executePreMoveAction(Direction direction) override;
    virtual bool isPassablePlayer() override;
};

#endif /* defined(__solno__MovableRock__) */
