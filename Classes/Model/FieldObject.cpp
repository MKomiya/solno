//
//  FieldObject.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#include "FieldObject.h"
#include "Direction.h"

#include "MovableRock.h"
#include "MessagePoint.h"

#pragma mark create method
FieldObject* FieldObject::create(int id, cocos2d::Point pos, std::string type_str, std::string optional_params)
{
    FieldObject* ret;
    if (type_str == "1") {
        ret = new MovableRock();
        ret->setObjectType(MOVABLE_ROCK);
    } else if (type_str == "2") {
        ret = new MessagePoint();
        ret->setObjectType(MESSAGE_POINT);
    } else if (type_str == "3") {
        ret = new FieldObject();
        ret->setObjectType(START_POINT);
    }
    
    ret->setId(id);
    ret->setPosition(pos);
    ret->setOptionalParams(optional_params);
    return ret;
}

#pragma mark override method
void FieldObject::executePreMoveAction(Direction d, FieldLayer* v)
{
}

void FieldObject::executeDecideAction()
{
}

void FieldObject::executeMovedAction(FieldLayer* v)
{
}

bool FieldObject::isPassablePlayer()
{
    return true;
}