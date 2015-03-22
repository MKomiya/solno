//
//  StoryPoint.cpp
//  solno
//
//  Created by S_Wyvern on 2015/03/21.
//
//

#include "StoryPoint.h"
#include "FieldState.h"
#include "FieldLayer.h"
#include "StoryState.h"
#include "Router.h"

USING_NS_CC;

StoryPoint::StoryPoint(FieldState* state, int id, cocos2d::ValueMap data) :
    FieldObject(state, id, data)
{
    setStoryId(data["story_id"].asString());
}

void StoryPoint::executeDecideAction()
{
    auto view = state->getFieldView();
    
    auto fade = FadeOut::create(0.3f);
    auto change_state = CallFunc::create([]() {
        auto router = Raciela::Router::getInstance();
        router->pushState(StoryState::create());
    });
    auto action = Sequence::create(fade, change_state, nullptr);
    view->runAction(action);
}

bool StoryPoint::isPassablePlayer()
{
    return false;
}