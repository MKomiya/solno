//
//  MovableRock.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#include "MovableRock.h"

#include "FieldState.h"
#include "FieldLayer.h"

MovableRock::MovableRock(FieldState* state, int id, cocos2d::ValueMap data) :
    FieldObject(state, id, data)
{
}

void MovableRock::executePreMoveAction(Direction direction)
{
    auto check_pos = this->getPosition() + direction.getMapPointVec();
    if (state->isCollidable(check_pos.x, check_pos.y)) {
        return ;
    }
    
    pos += direction.getMapPointVec();
    auto move_vec = direction.getUnitVec() * 16;
    
    auto view = state->getFieldView();
    view->runObjectMoveAction(getId(), move_vec);
}

bool MovableRock::isPassablePlayer()
{
    return false;
}