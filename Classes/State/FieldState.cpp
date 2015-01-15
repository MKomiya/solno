//
//  FieldState.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "FieldState.h"

#include "FieldLayer.h"
#include "ControllerLayer.h"
#include "MessageView.h"

#include "Direction.h"

USING_NS_CC;

FieldState::FieldState(FieldLayer* view, ControllerLayer* controller) :
player_map_pos(Point(0, 0)),
player_direction("down"),
view(view),
controller(controller)
{
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
            
            std::string type_str = object_data["type"].asString();
            ObjectType type;
            std::string optional_params = "";
            if (type_str == "1") {
                type = MOVABLE_ROCK;
            } else if (type_str == "2") {
                type = MESSAGE_POINT;
                optional_params = object_data["msg_data"].asString();
            } else if (type_str == "3") {
                type = START_POINT;
                player_map_pos = Point(x, y);
            }
            auto ret = new FieldObject(id, Point(x, y), type, optional_params);
            objects.push_back(ret);
            ++id;
        }
    }
    
    view->initFieldObject(objects);
}

FieldState::~FieldState()
{
}

void FieldState::update()
{
    
    auto event = InputModule::getInstance()->popEvent();
    
    if (event == InputEvent::RELEASE_DECIDE) {
        // message view disabled
        if (view->getMessageState() == MessageView::WAIT) {
            view->releaseMessages();
            controller->setEnableArrowButtons(true);
        }
    }
    
    if (event != InputEvent::RELEASE_DECIDE && event != InputEvent::PRESS_DECIDE && event != 0) {
        movePlayerCharacter(event);
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
        if (obj->pos == next_pos) {
            // check collidable behind movable rock
            if (obj->type == ObjectType::MOVABLE_ROCK) {
                Point check_pos = obj->pos;
                check_pos += direction_entity.getMapPointVec();
                if (isCollidable(check_pos.x, check_pos.y)) {
                    return ;
                }
                
                // moving rock action
                Point move_vec;
                obj->pos += direction_entity.getMapPointVec();
                move_vec  = direction_entity.getUnitVec() * 16;
                
                // send run action map object
                view->runObjectMoveAction(obj->id, move_vec);
                
                break;
            }
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
        if (obj->pos == player_map_pos) {
            if (obj->type == ObjectType::MESSAGE_POINT) {
                controller->setEnableArrowButtons(false);
                auto action = CallFunc::create([=]() {
                    view->viewMessages(obj->optional_params);
                });
                view->addRunActionAfterMove(action);
            }
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
    
    return false;
}