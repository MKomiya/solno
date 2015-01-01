//
//  FieldLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/26.
//
//

#include "FieldLayer.h"

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
    auto map = TMXTiledMap::create("tmx/largemap.tmx");
    map->setAnchorPoint(Point(0, 1));
    map->setPosition(Point(16, s.height - 16));
    map->setScale(2.0f);
    addChild(map);
    auto collider = map->getLayer("meta");
    
    // player character view
    Director::getInstance()->getTextureCache()->addImage("chara/hiroine_3232.png");
    auto frame_cache = SpriteFrameCache::getInstance();
    frame_cache->addSpriteFramesWithFile("chara/hiroine.plist", "chara/hiroine_3232.png");

    player_sprite = Sprite::create();
    auto cache  = AnimationCache::getInstance();
    cache->addAnimationsWithFile("chara/animations.plist");
    auto animation = cache->getAnimation("left_anime");
    
    player_idling_animate = Animate::create(animation);
    player_sprite->runAction(player_idling_animate);
    player_sprite->setAnchorPoint(Point(0, 1));
    player_sprite->setPosition(Point(16, s.height - 16));
    addChild(player_sprite);
    
    // Initialize state
    {
        auto state = new FieldState(this, collider);
        auto state_machine = StateMachineModule::getInstance();
        state_machine->registerState("field", state);
        state_machine->setNowState("field");
        
        scheduleUpdate();
    }
    
    return true;
}

void FieldLayer::changePlayerAnimation(std::string direction)
{
    auto anime_name = direction + "_anime";
    auto animation  = AnimationCache::getInstance()->getAnimation(anime_name.c_str());
    player_idling_animate->setAnimation(animation);
}

bool FieldLayer::runMoveAction(cocos2d::Point move_vec)
{
    auto running_action = player_sprite->getActionByTag(PlayerActionTags::MOVE_SEQUENCE);
    if (running_action != NULL && !running_action->isDone()) {
        return false;
    }
    
    auto move_action = MoveBy::create(0.3f, move_vec);
    move_action->setTag(PlayerActionTags::MOVE_SEQUENCE);
    player_sprite->runAction(move_action);
    return true;
}

void FieldLayer::update(float dt)
{
    CCLOG("FieldLayer: update");
    StateMachineModule::getInstance()->update();
}