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
#include "UserStorageModule.h"

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
    auto change_state = CallFunc::create([=]() {
        auto player_pos = state->getPlayerMapPosition();
        UserStorageModule::getInstance()->updatePlayerPosition(state->getMapId(), player_pos);
        Raciela::Router::getInstance()->replaceState(StoryState::createByStoryId(story_id));
    });
    auto action = Sequence::create(fade, change_state, nullptr);
    view->runAction(action);
}

bool StoryPoint::isPassablePlayer()
{
    return false;
}
