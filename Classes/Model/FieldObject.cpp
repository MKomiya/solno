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
#include "Tree.h"
#include "FieldState.h"

#pragma mark create method
FieldObject* FieldObject::create(FieldState* state, int id, cocos2d::ValueMap data)
{
    auto type_str = data["type"].asString();
    
    auto size = state->getMap()->getLayer("meta")->getLayerSize();
    float x   = data["x"].asFloat() / 16;
    float y   = size.height - data["y"].asFloat() / 16 - 1;
    auto pos  = cocos2d::Point(x, y);
    
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
    
    } else if (type_str == "4") {
        auto ret = new Tree();
        ret->setObjectType(TREE);
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

int FieldObject::getBreakItemId()
{
    return 0;
}