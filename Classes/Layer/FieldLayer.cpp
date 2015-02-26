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

#include "FieldState.h"
#include "FieldObject.h"
#include "Dispatcher.h"

USING_NS_CC;

bool FieldLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    // msg_view
    msg_view = MessageView::create();
    addChild(msg_view);
    
    return true;
}

void FieldLayer::initMapData(cocos2d::TMXTiledMap *value)
{
    auto s = Director::getInstance()->getWinSize();
    
    // map view
    map = value;
    map->setAnchorPoint(Point(0, 1));
    map->setPosition(Point(16, s.height - 16));
    map->setScale(2.0f);
    addChild(map);
    
    // invisible meta
    auto meta_layer = map->getLayer("meta");
    meta_layer->setVisible(false);
}

void FieldLayer::initFieldObject(std::vector<FieldObject *> objects)
{
    auto s = map->getContentSize();
    
    objects_root = Node::create();
    objects_root->setPosition(Point::ZERO);
    map->addChild(objects_root);
    
    for (FieldObject* object : objects) {
        auto obj_pos = object->getPosition();
        if (object->getObjectType() == FieldObject::ObjectType::START_POINT) {
            Point map_scroll_vec;
            map_scroll_vec.x = floorf(object->getPosition().x / 8) * -32 * 9;
            map_scroll_vec.y = floorf(object->getPosition().y / 8) * 32 * 9;
            map->setPosition(map->getPosition() + map_scroll_vec);
            
            auto obj_x = obj_pos.x > 8 ? (int)obj_pos.x % 9 : obj_pos.x;
            auto obj_y = obj_pos.y > 8 ? (int)obj_pos.y % 9 : obj_pos.y;
            
            auto win_size = Director::getInstance()->getWinSize();
            Point pos;
            pos.x = obj_x * 32  + 16;
            pos.y = obj_y * -32 + (win_size.height - 16);
            
            player_sprite = PlayerView::create();
            player_sprite->setAnchorPoint(Point(0, 1));
            player_sprite->setPosition(pos);
            addChild(player_sprite);
            
            continue;
        }
        
        Point pos;
        pos.x = obj_pos.x * 16;
        pos.y = s.height - (obj_pos.y * 16);
        
        auto sprite = Sprite::create("tmx/movable_rock.png");
        sprite->getTexture()->setAliasTexParameters();
        sprite->setAnchorPoint(Point(0, 1));
        sprite->setPosition(pos);
        sprite->setTag(object->getId());
        objects_root->addChild(sprite);
    }
}

void FieldLayer::changePlayerAnimation(std::string direction)
{
    player_sprite->setIdlingAnimate(direction.c_str());
}

void FieldLayer::stopPlayerAnimation()
{
    player_sprite->setIdlingAnimate("stop");
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

void FieldLayer::scrollField(cocos2d::Point move_vec, cocos2d::Point scroll_vec)
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    
    auto action = Sequence::create(
                                   Spawn::create(TargetedAction::create(player_sprite, MoveBy::create(0.4, move_vec)),
                                                 TargetedAction::create(map, MoveBy::create(0.4, scroll_vec)), nullptr),
                                   CallFunc::create([dispatcher]() {
                                       dispatcher->dispatch("update_field_state", FieldViewState::NOTHING);
                                   }), nullptr);
    action->setTag(SCROLL_ACTION);
    
    dispatcher->dispatch("update_field_state", FieldViewState::SCROLL);
    runAction(action);
}

void FieldLayer::addRunActionAfterMove(cocos2d::FiniteTimeAction *action)
{
    player_sprite->addRunActionAfterMove(action);
}

void FieldLayer::viewMessages(std::vector<std::string> msg_data)
{
    msg_view->viewMessages(msg_data);
}

void FieldLayer::releaseMessages()
{
    msg_view->nextMessage();
}

void FieldLayer::destroyObject(int id)
{
    auto target = objects_root->getChildByTag(id);
    if (target == nullptr) {
        return ;
    }
    
    target->runAction(Sequence::create(FadeOut::create(0.3f),
                                       RemoveSelf::create(),
                                       NULL));
}