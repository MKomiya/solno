//
//  FieldLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/26.
//
//

#include "FieldLayer.h"
#include "PlayerView.h"

#include "StateMachineModule.h"
#include "FieldState.h"

USING_NS_CC;

bool FieldLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto s = Director::getInstance()->getWinSize();
    
    // map view
    map = TMXTiledMap::create("tmx/largemap.tmx");
    map->setAnchorPoint(Point(0, 1));
    map->setPosition(Point(16, s.height - 16));
    map->setScale(2.0f);
    addChild(map);
    
    // player character view
    player_sprite = PlayerView::create();
    player_sprite->setAnchorPoint(Point(0, 1));
    player_sprite->setPosition(Point(16, s.height - 16));
    addChild(player_sprite);
    
    return true;
}

void FieldLayer::changePlayerAnimation(std::string direction)
{
    player_sprite->setIdlingAnimate(direction.c_str());
}

void FieldLayer::runMoveAction(cocos2d::Point move_vec)
{    
    player_sprite->runMoveAction(move_vec);
}

TMXLayer* FieldLayer::getMapCollider()
{
    auto ret = map->getLayer("meta");
    if (ret == nullptr) {
        throw "meta layer is not found";
    }
    return ret;
}

void FieldLayer::scrollField(cocos2d::Point move_vec, cocos2d::Point scroll_vec)
{
    auto action = Spawn::create(TargetedAction::create(player_sprite, MoveBy::create(0.4, move_vec)),
                                TargetedAction::create(map, MoveBy::create(0.4, scroll_vec)), nullptr);
    action->setTag(SCROLL_ACTION);
    this->runAction(action);
}

bool FieldLayer::isRunningPlayerView()
{
    return player_sprite->isRunnningMoveAction();
}

bool FieldLayer::isRunningMapScroll()
{
    auto action = this->getActionByTag(SCROLL_ACTION);
    if (action && !action->isDone()) {
        return true;
    }
    return false;
}