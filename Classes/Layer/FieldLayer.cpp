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
    meta_layer->setVisible(false);
    obj_layer->setVisible(false);
    
    // player character view
    /*
    player_sprite = PlayerView::create();
    player_sprite->setAnchorPoint(Point(0, 1));
    player_sprite->setPosition(Point(16, s.height - 16));
    addChild(player_sprite);
    */
    
    // msg_view
    msg_view = MessageView::create();
    addChild(msg_view);
    
    return true;
}

void FieldLayer::initFieldObject(std::vector<FieldObject *> objects)
{
    auto s = map->getContentSize();
    
    objects_root = Node::create();
    objects_root->setPosition(Point::ZERO);
    map->addChild(objects_root);
    
    for (auto object : objects) {
        if (object->type == ObjectType::START_POINT) {
            Point map_scroll_vec;
            map_scroll_vec.x = floorf(object->pos.x / 8) * -32 * 9;
            map_scroll_vec.y = floorf(object->pos.y / 8) * 32 * 9;
            map->setPosition(map->getPosition() + map_scroll_vec);
            
            auto obj_x = object->pos.x > 8 ? (int)object->pos.x % 9 : object->pos.x;
            auto obj_y = object->pos.y > 8 ? (int)object->pos.y % 9 : object->pos.y;
            
            auto win_size = Director::getInstance()->getWinSize();
            Point pos;
            pos.x = obj_x * 32  + 16;
            pos.y = obj_y * -32 + (win_size.height - 16);
            
            player_sprite = PlayerView::create();
            player_sprite->setAnchorPoint(Point(0, 1));
            player_sprite->setPosition(pos);
            addChild(player_sprite);
        } else {
            Point pos;
            pos.x = object->pos.x * 16;
            pos.y = s.height - (object->pos.y * 16);
            
            auto sprite = Sprite::create("tmx/movable_rock.png");
            sprite->getTexture()->setAliasTexParameters();
            sprite->setAnchorPoint(Point(0, 1));
            sprite->setPosition(pos);
            sprite->setTag(object->id);
            objects_root->addChild(sprite);
        }
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

TMXObjectGroup* FieldLayer::getObjectsGroup()
{
    auto group = map->getObjectGroup("Event");
    if (group == nullptr) {
        throw "object group is not found";
    }
    return group;
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

void FieldLayer::addRunActionAfterMove(cocos2d::FiniteTimeAction *action)
{
    player_sprite->addRunActionAfterMove(action);
}

void FieldLayer::viewMessages(std::string msg_data)
{
    msg_view->viewMessages(msg_data);
}

void FieldLayer::releaseMessages()
{
    msg_view->nextMessage();
}

MessageView::ViewState FieldLayer::getMessageState()
{
    return msg_view->getState();
}