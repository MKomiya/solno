//
//  FieldLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/26.
//
//

#include "FieldLayer.h"
#include "PlayerView.h"
#include "MessageView.h"

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
    
    // invisible meta
    auto meta_layer = map->getLayer("meta");
    auto obj_layer  = map->getLayer("object");
    meta_layer->setVisible(true);
    obj_layer->setVisible(false);
    
    // player character view
    player_sprite = PlayerView::create();
    player_sprite->setAnchorPoint(Point(0, 1));
    player_sprite->setPosition(Point(16, s.height - 16));
    addChild(player_sprite);
    
    // test add
    auto message_view = MessageView::create("テストメッセージ");
    addChild(message_view);
    
    return true;
}

void FieldLayer::initFieldObject(std::vector<FieldObject *> objects)
{
    auto s = map->getContentSize();
    
    objects_root = Node::create();
    objects_root->setPosition(Point::ZERO);
    map->addChild(objects_root);
    
    for (auto object : objects) {
        auto sprite = Sprite::create("tmx/movable_rock.png");
        Point pos;
        pos.x = object->pos.x * 16;
        pos.y = s.height - (object->pos.y * 16);
        
        sprite->getTexture()->setAliasTexParameters();
        sprite->setAnchorPoint(Point(0, 1));
        sprite->setPosition(pos);
        sprite->setTag(object->id);
        objects_root->addChild(sprite);
    }
}

void FieldLayer::changePlayerAnimation(std::string direction)
{
    player_sprite->setIdlingAnimate(direction.c_str());
}

void FieldLayer::runMoveAction(cocos2d::Point move_vec)
{    
    player_sprite->runMoveAction(move_vec);
}

void FieldLayer::runObjectMoveAction(int object_id, cocos2d::Point move_vec)
{
    auto obj = objects_root->getChildByTag(object_id);
    
    obj->runAction(MoveBy::create(0.3, move_vec));
}

TMXLayer* FieldLayer::getMapCollider()
{
    auto ret = map->getLayer("meta");
    if (ret == nullptr) {
        throw "meta layer is not found";
    }
    return ret;
}

TMXLayer* FieldLayer::getObjectsLayer()
{
    auto ret = map->getLayer("object");
    if (ret == nullptr) {
        throw "object layer is not found";
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