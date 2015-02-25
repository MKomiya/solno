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
FieldObject* FieldObject::create(FieldState* state, int id, cocos2d::Point pos, cocos2d::ValueMap data)
{
    auto type_str = data["type"].asString();
    
    if (type_str == "1") {
        auto ret = new MovableRock();
        ret->setObjectType(MOVABLE_ROCK);
        ret->setId(id);
        ret->setPosition(pos);
        ret->setFieldState(state);
        return ret;
        
    } else if (type_str == "2") {
        auto ret = new MessagePoint();
        ret->setObjectType(MESSAGE_POINT);
        ret->setMessageData(data["msg_data"].asString());
        ret->setDecideTrigger(data["decide_trigger"].asBool());
        ret->setId(id);
        ret->setPosition(pos);
        ret->setFieldState(state);
        return ret;
        
    } else if (type_str == "3") {
        auto ret = new FieldObject();
        ret->setObjectType(START_POINT);
        ret->setId(id);
        ret->setPosition(pos);
        ret->setFieldState(state);
        return ret;
    }
    return nullptr;
}

#pragma mark override method
void FieldObject::executePreMoveAction(Direction d)
{
}

void FieldObject::executeDecideAction()
{
}

void FieldObject::executeMovedAction()
{
}

bool FieldObject::isPassablePlayer()
{
    return true;
}