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
    
    this->pos += direction.getMapPointVec();
    auto move_vec = direction.getUnitVec() * 16;
    
    view->runObjectMoveAction(this->getId(), move_vec);
}