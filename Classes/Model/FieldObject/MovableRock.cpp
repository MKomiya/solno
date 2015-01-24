//
//  MovableRock.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#include "MovableRock.h"

#include "FieldLayer.h"

void MovableRock::executePreMoveAction(Direction direction, FieldLayer* view)
{
    auto check_pos = this->getPosition() + direction.getMapPointVec();
    if (this->isCollidable(check_pos, view)) {
        return ;
    }
    
    this->pos += direction.getMapPointVec();
    auto move_vec = direction.getUnitVec() * 16;
    
    view->runObjectMoveAction(this->getId(), move_vec);
}

bool MovableRock::isPassablePlayer()
{
    return false;
}

bool MovableRock::isCollidable(cocos2d::Point pos, FieldLayer* view)
{
    if (pos.x < 0 || pos.y < 0) {
        return true;
    }
    
    auto tiled_gid = view->getMapCollider()->getTileGIDAt(pos);
    
    if (tiled_gid > 0) {
        return true;
    }
    
    return false;
}