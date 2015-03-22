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
#include "StoryPoint.h"
#include "FieldState.h"

FieldObject::FieldObject(FieldState* state, int id, cocos2d::ValueMap data)
{
    auto size = state->getMap()->getLayer("meta")->getLayerSize();
    float x   = data["x"].asFloat() / 16;
    float y   = size.height - data["y"].asFloat() / 16 - 1;
    auto pos  = cocos2d::Point(x, y);
    auto type = (ObjectType)std::stoi(data["type"].asString());
    
    setId(id);
    setPosition(pos);
    setFieldState(state);
    setObjectType(type);
}

#pragma mark create method
FieldObject* FieldObject::create(FieldState* state, int id, cocos2d::ValueMap data)
{
    auto type = (ObjectType)std::stoi(data["type"].asString());
    
    switch (type) {
        case MOVABLE_ROCK:
            return new MovableRock(state, id, data);
        case MESSAGE_POINT:
            return new MessagePoint(state, id, data);
        case START_POINT:
            return new FieldObject(state, id, data);
        case TREE:
            return new Tree(state, id, data);
        case STORY_POINT:
            return new StoryPoint(state, id, data);
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