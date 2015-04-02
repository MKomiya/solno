//
//  FieldState.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include <json11.hpp>

#include "FieldState.h"
#include "ModeSelectMenuState.h"
#include "Direction.h"
#include "FieldObject.h"
#include "Item.h"
#include "MasterStorageModule.h"
#include "UserStorageModule.h"
#include "Dispatcher.h"
#include "Router.h"
#include "ViewManager.h"

#include "FieldLayer.h"
#include "ControllerLayer.h"
#include "FieldControllerLayer.h"
#include "StoryLayer.h"
#include "MessageView.h"
#include "PlayerView.h"
#include "MenuArrowItem.h"

USING_NS_CC;

FieldState* FieldState::create()
{
    auto ret = new FieldState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    // initialize view
    auto field      = FieldLayer::create();
    auto frame      = ControllerLayer::create();
    auto controller = FieldControllerLayer::create();
    auto view_manager = Raciela::ViewManager::getInstance();
    view_manager->addView(field);
    view_manager->addView(frame);
    view_manager->addView(controller);
    
    ret->init();
    ret->setMap(TMXTiledMap::create("tmx/01_scrap.tmx"));
    ret->setMapId(1);
    ret->setPlayerMapPosition(Point(0, 0));
    ret->setPlayerDirection("down");
    ret->setFieldView(field);
    ret->setFrameView(frame);
    ret->setControllerView(controller);
    ret->setExecuteItem(nullptr);
    
    ret->setMsgViewState(MessageViewState::DISABLED);
    ret->setPlayerViewState(PlayerViewState::IDLING);
    ret->setFieldViewState(FieldViewState::NOTHING);
    
    UserStorageModule::getInstance()->init();
    
    ret->autorelease();
    ret->loadMapData();
    return ret;
}

void FieldState::loadMapData()
{
    auto obj_group = map->getObjectGroup("Event");
    
    int id = 100;
    for (auto object : obj_group->getObjects()) {
        auto object_data = object.asValueMap();
        
        auto ret = FieldObject::create(this, id, object_data);
        objects.push_back(ret);
        ++id;
        
        if (ret->getObjectType() == FieldObject::ObjectType::START_POINT) {
            player_map_pos = ret->getPosition();
        }
    }
    
    view->initMapData(map);
    view->initFieldObject(objects);
}

void FieldState::enter()
{
    delegate();
    if (controller) {
        controller->setVisible(true);
    }
}

void FieldState::update()
{
    if (execute_item != nullptr) {
        execute_item->useItem(this);
        execute_item = nullptr;
        view->changePlayerAnimation(player_direction);
        return ;
    }
}

void FieldState::exit()
{
    Raciela::State::exit();
    Raciela::ViewManager::getInstance()->removeView(view);
}

void FieldState::resume()
{
    dispatcher->dispose_transition("use_item");

    delegate();
    if (controller) {
        controller->setVisible(true);
    }
    view->changePlayerAnimation(player_direction);
}

void FieldState::pause()
{
    Raciela::State::pause();
    
    view->stopPlayerAnimation();
    controller->setVisible(false);

    dispatcher->subscribe_transition<void (Item*)>("use_item", [=](Item* item) {
        addExecuteItem(item);
    });
}

void FieldState::addExecuteItem(Item* item)
{
    execute_item = item;
}

void FieldState::delegate()
{
    dispatcher->subscribe<void (Item*)>("execute_item", [=](Item* item) {
        addExecuteItem(item);
    });
    
    dispatcher->subscribe<void (ArrowInputEvent)>("input_arrow", [=](ArrowInputEvent e) {
        movePlayerCharacter(e);
    });
    
    dispatcher->subscribe<void ()>("release_decide", [=]() {
        decideAction();
    });
    
    dispatcher->subscribe<void ()>("release_menu", [=]() {
         Raciela::Router::getInstance()->pushState(ModeSelectMenuState::create());
    });
    
    dispatcher->subscribe<void (MessageViewState)>("update_msg_state", [=](MessageViewState state) {
        msg_view_state = state;
    });
    
    dispatcher->subscribe<void (PlayerViewState)>("update_player_state", [=](PlayerViewState state) {
        player_view_state = state;
    });
    
    dispatcher->subscribe<void (FieldViewState)>("update_field_state", [=](FieldViewState state) {
        field_view_state = state;
    });
    
    dispatcher->subscribe<void (Item*)>("use_item", [=](Item* item) {
        addExecuteItem(item);
    });
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
    // message view disabled
    if (msg_view_state == MessageViewState::WAIT) {
        view->releaseMessages();
        controller->setEnableArrowButtons(true);
        return ;
    }

    auto direction_entity = Direction::createInstance(player_direction);
    auto next_pos = player_map_pos + direction_entity.getMapPointVec();
    
    // check object executable
    for (auto obj : objects) {
        if (obj->getPosition() == next_pos) {
            obj->executeDecideAction();
        }
    }
}

void FieldState::movePlayerCharacter(ArrowInputEvent event)
{
    if (player_view_state == PlayerViewState::RUNNING ||
        field_view_state == FieldViewState::SCROLL) {
        return ;
    }
    
    if (event == ArrowInputEvent::RELEASE_DOWN  ||
        event == ArrowInputEvent::RELEASE_LEFT  ||
        event == ArrowInputEvent::RELEASE_RIGHT ||
        event == ArrowInputEvent::RELEASE_UP) {
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
            obj->executePreMoveAction(direction_entity);
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
    if (((int)player_map_pos.x % 9 == 0 && event == ArrowInputEvent::PRESS_RIGHT) ||
        ((int)player_map_pos.y % 9 == 0 && event == ArrowInputEvent::PRESS_DOWN)  ||
        ((int)player_map_pos.x % 9 == 8 && event == ArrowInputEvent::PRESS_LEFT)  ||
        ((int)player_map_pos.y % 9 == 8 && event == ArrowInputEvent::PRESS_UP))
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
            obj->executeMovedAction();
        }
    }
}

bool FieldState::isCollidable(int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0) {
        return true;
    }
    
    auto tiled_gid = map->getLayer("meta")->getTileGIDAt(Point(map_x, map_y));
    
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
