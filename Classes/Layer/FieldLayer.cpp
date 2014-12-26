//
//  FieldLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/26.
//
//

#include "FieldLayer.h"

USING_NS_CC;

bool FieldLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto s = Director::getInstance()->getWinSize();
    
    // map view
    {
        auto map = TMXTiledMap::create("tmx/largemap.tmx");
        map->setScale(2.0f);
        addChild(map);
    }
    
    // player character view
    {
        auto texture = Director::getInstance()->getTextureCache()->addImage("chara/hiroine_1616.png");
        texture->setAliasTexParameters();
        
        auto frame_cache = SpriteFrameCache::getInstance();
        frame_cache->addSpriteFramesWithFile("chara/hiroine.plist", "chara/hiroine_1616.png");

        auto sprite = Sprite::create();
        auto cache  = AnimationCache::getInstance();
        cache->addAnimationsWithFile("chara/animations.plist");
        auto animation = cache->getAnimation("down_anime");
        
        player_idling_animate = Animate::create(animation);
        sprite->runAction(player_idling_animate);
        sprite->setScale(2.0f);
        sprite->setPosition(Point(s.width / 2.0f, s.height / 2.0f));
        addChild(sprite);
    }
    
    return true;
}

void FieldLayer::_changePlayerAnimation(std::string direction)
{
    auto anime_name = direction + "_anime";
    auto animation  = AnimationCache::getInstance()->getAnimation(anime_name.c_str());
    player_idling_animate->setAnimation(animation);
}