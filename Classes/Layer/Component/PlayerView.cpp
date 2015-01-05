//
//  PlayerView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/05.
//
//

#include "PlayerView.h"

USING_NS_CC;

PlayerView* PlayerView::create()
{
    auto ret = new PlayerView();
    if (ret && ret->init()) {
        ret->autorelease();
        
        // スプライトアニメーションの読み込みと登録
        auto frame_cache = SpriteFrameCache::getInstance();
        frame_cache->addSpriteFramesWithFile("chara/hiroine.plist", "chara/hiroine_3232.png");
        auto cache  = AnimationCache::getInstance();
        cache->addAnimationsWithFile("chara/animations.plist");
        auto animation = cache->getAnimation("down_anime");
        auto animate   = Animate::create(animation);
        animate->setTag(IDLING_ANIMATE);
        ret->runAction(animate);
    } else {
        delete ret;
        ret = NULL;
    }
    return ret;
}

void PlayerView::setIdlingAnimate(std::string direction)
{
    // 既存のアニメーションを止める
    stopActionByTag(IDLING_ANIMATE);
    
    auto anime_name = direction + "_anime";
    auto animation  = AnimationCache::getInstance()->getAnimation(anime_name.c_str());
    auto animate    = Animate::create(animation);
    animate->setTag(IDLING_ANIMATE);
    runAction(animate);
}

bool PlayerView::runMoveAction(Point move_vec, std::string direction = "")
{
    auto hoge = CallFunc::create([]() {
        CCLOG("action called");
    });
    this->runAction(hoge);
    
    auto action = this->getActionByTag(PlayerView::PlayerActionTag::MOVE_SEQUENCE);
    if (action && !action->isDone()) {
        return false;
    }
    
    // 方向が変わるときにのみdirection指定
    if (direction.empty()) {
        auto move_action = MoveBy::create(0.3f, move_vec);
        move_action->setTag(MOVE_SEQUENCE);
        this->runAction(move_action);
    } else {
        auto change_dir  = CallFunc::create([=]() {
            this->setIdlingAnimate(direction);
        });
        auto move_action = MoveBy::create(0.3f, move_vec);
        auto seq         = Sequence::create(change_dir, move_action, NULL);
        seq->setTag(MOVE_SEQUENCE);
        this->runAction(seq);
    }
    return true;
}