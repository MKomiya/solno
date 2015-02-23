//
//  PlayerView.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/05.
//
//

#include "PlayerView.h"
#include "Dispatcher.h"

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
        
        return ret;
    }
    
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void PlayerView::setIdlingAnimate(std::string direction)
{
    // 既存のアニメーションを止める
    stopActionByTag(IDLING_ANIMATE);
    // 停止命令ならそのまま止める
    if (direction == "stop") {
        return ;
    }
    
    auto anime_name = direction + "_anime";
    auto animation  = AnimationCache::getInstance()->getAnimation(anime_name.c_str());
    auto animate    = Animate::create(animation);
    animate->setTag(IDLING_ANIMATE);
    runAction(animate);
}

void PlayerView::runMoveAction(Point move_vec)
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    
    auto move_action = MoveBy::create(0.3f, move_vec);
    auto moved_action = CallFunc::create([this,dispatcher]() {
        if (after_move_action.size() == 0) {
            dispatcher->dispatch("update_player_state", PlayerViewState::IDLING);
            return ;
        }
        
        auto seq = Sequence::create(after_move_action);
        auto after = CallFunc::create([this,dispatcher]{
            dispatcher->dispatch("update_player_state", PlayerViewState::IDLING);
            after_move_action.clear();
        });
        
        runAction(Sequence::create(seq, after, NULL));
    });
    auto action = Sequence::create(move_action, moved_action, NULL);
    action->setTag(MOVE_SEQUENCE);
    
    dispatcher->dispatch("update_player_state", PlayerViewState::RUNNING);
    runAction(action);
}

void PlayerView::addRunActionAfterMove(cocos2d::FiniteTimeAction *action)
{
    after_move_action.pushBack(action);
}