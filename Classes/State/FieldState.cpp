//
//  FieldState.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include <json11.hpp>

#include "StateMachineModule.h"
#include "FieldState.h"
#include "StoryState.h"
#include "Direction.h"
#include "FieldObject.h"
#include "Item.h"
#include "MasterStorageModule.h"

#include "LayerManager.h"
#include "FieldLayer.h"
#include "ControllerLayer.h"
#include "StoryLayer.h"
#include "MessageView.h"

USING_NS_CC;

FieldState* FieldState::create(FieldLayer *view, ControllerLayer *controller)
{
    auto ret = new FieldState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->setPlayerMapPosition(Point(0, 0));
    ret->setPlayerDirection("down");
    ret->setFieldView(view);
    ret->setControllerView(controller);
    ret->setExecuteItem(nullptr);
    
    ret->autorelease();
    return ret;
}

void FieldState::enter()
{
    if (execute_item != 0) {
        CCLOG("use item. item_id: %d, item_type: %d", execute_item->getItemId(), execute_item->getType());
        execute_item = nullptr;
        view->changePlayerAnimation(player_direction);
        return ;
    }
    
    // map size取得のためにcollider layerで代用する
    auto obj_layer = view->getMapCollider();
    auto size      = obj_layer->getLayerSize();
    auto obj_group = view->getObjectsGroup();
    
    {
        int id = 100;
        for (auto object : obj_group->getObjects()) {
            auto object_data = object.asValueMap();
            
            float x  = object_data["x"].asFloat() / 16;
            float y  = size.height - object_data["y"].asFloat() / 16 - 1;
            auto pos = Point(x, y);
            
            auto ret = FieldObject::create(id, pos, object_data);
            objects.push_back(ret);
            ++id;
            
            if (ret->getObjectType() == FieldObject::ObjectType::START_POINT) {
                player_map_pos = ret->getPosition();
            }
        }
    }
    
    view->initFieldObject(objects);
}

void FieldState::update()
{
    auto event = InputModule::getInstance()->popEvent();
    
    if (event == InputEvent::RELEASE_DECIDE) {
        decideAction();
    }
    
    if (event != InputEvent::RELEASE_DECIDE && event != InputEvent::PRESS_DECIDE && event != 0) {
        movePlayerCharacter(event);
    }
}

void FieldState::exit()
{
    view->stopPlayerAnimation();
}

void FieldState::addExecuteItem(Item* item)
{
    execute_item = item;
}

FieldObject* FieldState::findPlayerDirectionAbutObject()
{
    auto direction  = Direction::createInstance(player_direction);
    auto search_pos = player_map_pos + direction.getMapPointVec();
    
    for (auto obj : objects) {
        if (obj->getPosition() == search_pos) {
            return obj;
        }
    }
    return nullptr;
}

void FieldState::deleteObject(FieldObject *target)
{
    auto it = objects.begin();
    for (; it != objects.end(); ++it) {
        if ((*it) == target) {
            objects.erase(it);
            return ;
        }
    }
    
    CCLOG("破壊オブジェクトがないよ");
}

void FieldState::decideAction()
{
    StateMachineModule::getInstance()->changeState("mode_select_menu");
    return ;
    
    // message view disabled
    if (view->getMessageState() == MessageView::WAIT) {
        view->releaseMessages();
        controller->setEnableArrowButtons(true);
        return ;
    }
    

    auto direction_entity = Direction::createInstance(player_direction);
    auto next_pos = player_map_pos + direction_entity.getMapPointVec();
    
    // check object executable
    for (auto obj : objects) {
        if (obj->getPosition() == next_pos) {
            obj->executeDecideAction(view);
        }
    }
}

void FieldState::movePlayerCharacter(InputEvent event)
{
    if (view->isRunningPlayerView() || view->isRunningMapScroll()) {
        return ;
    }
    
    if (event == InputEvent::RELEASE_DOWN  ||
        event == InputEvent::RELEASE_LEFT  ||
        event == InputEvent::RELEASE_RIGHT ||
        event == InputEvent::RELEASE_UP) {
        return ;
    }
    
    std::string direction_str = player_direction;
    
    auto move_vec = Point(0, 0);
    auto next_pos = player_map_pos;
    
    auto direction_entity = Direction::createInstance(event);
    move_vec += direction_entity.getUnitVec() * 32;
    next_pos += direction_entity.getMapPointVec();
    direction_str = direction_entity.getDirectionLabel();
    
    if (player_direction != direction_str) {
        view->changePlayerAnimation(direction_str);
        player_direction = direction_str;
    }
    
    // check object collidable
    for (auto obj : objects) {
        if (obj->getPosition() == next_pos) {
            obj->executePreMoveAction(direction_entity, view);
        }
    }
    
    // check map collidable
    if (isCollidable(next_pos.x, next_pos.y)) {
        return ;
    }
    
    // update player position
    player_map_pos = next_pos;
    CCLOG("pos: (%f, %f)", player_map_pos.x, player_map_pos.y);
    
    // run scroll field if player pos is scroll point
    if (((int)player_map_pos.x % 9 == 0 && event == InputEvent::PRESS_RIGHT) ||
        ((int)player_map_pos.y % 9 == 0 && event == InputEvent::PRESS_DOWN)  ||
        ((int)player_map_pos.x % 9 == 8 && event == InputEvent::PRESS_LEFT)  ||
        ((int)player_map_pos.y % 9 == 8 && event == InputEvent::PRESS_UP))
    {
        Point move, scroll;
        move   = direction_entity.getUnitVec() * -32 * 8;
        scroll = direction_entity.getUnitVec() * -32 * 9;
        view->scrollField(move, scroll);
        
        return ;
    }
    
    // run move action
    view->runMoveAction(move_vec);
    
    // check object collidable after move
    for (auto obj : objects) {
        if (obj->getPosition() == player_map_pos) {
            obj->executeMovedAction(view);
        }
    }
}

bool FieldState::isCollidable(int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0) {
        return true;
    }
    
    auto tiled_gid = view->getMapCollider()->getTileGIDAt(Point(map_x, map_y));
    
    if (tiled_gid > 0) {
        return true;
    }
    
    auto pos = Point(map_x, map_y);
    for (auto object : objects) {
        if (object->getPosition() == pos && !object->isPassablePlayer()) {
            return true;
        }
    }
    
    return false;
}