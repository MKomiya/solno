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
    TMXLayer* collider;
    {
        auto map = TMXTiledMap::create("tmx/largemap.tmx");
        map->setScale(2.0f);
        addChild(map);
        collider = map->getLayer("meta");
    }
    
    // player character view
    {
        Director::getInstance()->getTextureCache()->addImage("chara/hiroine_3232.png");
        auto frame_cache = SpriteFrameCache::getInstance();
        frame_cache->addSpriteFramesWithFile("chara/hiroine.plist", "chara/hiroine_3232.png");

        auto sprite = Sprite::create();
        auto cache  = AnimationCache::getInstance();
        cache->addAnimationsWithFile("chara/animations.plist");
        auto animation = cache->getAnimation("left_anime");
        
        player_idling_animate = Animate::create(animation);
        sprite->runAction(player_idling_animate);
        sprite->setPosition(Point(s.width / 2.0f, s.height / 2.0f));
        addChild(sprite);
    }
    
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

void FieldLayer::update(float dt)
{
    CCLOG("FieldLayer: update");
    StateMachineModule::getInstance()->update();
}