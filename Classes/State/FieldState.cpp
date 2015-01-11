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

USING_NS_CC;

FieldState::FieldState(FieldLayer* view, ControllerLayer* controller) :
player_map_pos(Point(0, 0)),
player_direction("down"),
view(view),
controller(controller)
{
    auto obj_layer = view->getObjectsLayer();
    auto tiles     = obj_layer->getTiles();
    auto size      = obj_layer->getLayerSize();
    
    int id = 100;
    for (int i=0; i < size.width * size.height; ++i) {
        if (tiles[i] > 0) {
            Point pos(i % (int)size.width, i / (int)size.height);
            
            auto obj = new FieldObject(id, pos, MESSAGE_POINT);
            objects.push_back(obj);
            
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
    if (event != 0) {
        movePlayerCharacter(event);
    }
}

void FieldState::movePlayerCharacter(InputEvent event)
{
    if (view->isRunningPlayerView() || view->isRunningMapScroll()) {
        return ;
    }
    
    std::string direction_str = player_direction;
    
    auto move_vec = Point(0, 0);
    auto next_pos = player_map_pos;
    
    if (event == InputEvent::PRESS_UP) {
        direction_str = "up";
        move_vec.y = 32;
        next_pos.y -= 1;
    } else if (event == InputEvent::PRESS_LEFT) {
        direction_str = "left";
        move_vec.x = -32;
        next_pos.x -= 1;
    } else if (event == InputEvent::PRESS_DOWN) {
        direction_str = "down";
        move_vec.y = -32;
        next_pos.y += 1;
    } else if (event == InputEvent::PRESS_RIGHT) {
        direction_str = "right";
        move_vec.x = 32;
        next_pos.x += 1;
    }
    
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
                if (event == InputEvent::PRESS_DOWN) {
                    check_pos.y += 1;
                } else if (event == InputEvent::PRESS_LEFT) {
                    check_pos.x -= 1;
                } else if (event == InputEvent::PRESS_RIGHT) {
                    check_pos.x += 1;
                } else if (event == InputEvent::PRESS_UP) {
                    check_pos.y -= 1;
                }
                if (isCollidable(check_pos.x, check_pos.y)) {
                    return ;
                }
                
                // moving rock action
                Point move_vec;
                if (event == InputEvent::PRESS_DOWN) {
                    obj->pos.y += 1;
                    move_vec.y = -16;
                } else if (event == InputEvent::PRESS_LEFT) {
                    obj->pos.x -= 1;
                    move_vec.x = -16;
                } else if (event == InputEvent::PRESS_RIGHT) {
                    obj->pos.x += 1;
                    move_vec.x = 16;
                } else if (event == InputEvent::PRESS_UP) {
                    obj->pos.y -= 1;
                    move_vec.y = 16;
                }
                
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
    
    // run scroll field if player pos is scroll point
    if (((int)player_map_pos.x % 9 == 0 && event == InputEvent::PRESS_RIGHT) ||
        ((int)player_map_pos.y % 9 == 0 && event == InputEvent::PRESS_DOWN)  ||
        ((int)player_map_pos.x % 9 == 8 && event == InputEvent::PRESS_LEFT)  ||
        ((int)player_map_pos.y % 9 == 8 && event == InputEvent::PRESS_UP))
    {
        Point move, scroll;
        if (event == InputEvent::PRESS_RIGHT) {
            move = Point(-32 * 8, 0);
            scroll = Point(-32 * 9, 0);
        } else if (event == InputEvent::PRESS_DOWN) {
            move = Point(0, 32 * 8);
            scroll = Point(0, 32 * 9);
        } else if (event == InputEvent::PRESS_LEFT) {
            move = Point(32 * 8, 0);
            scroll = Point(32 * 9, 0);
        } else if (event == InputEvent::PRESS_UP) {
            move = Point(0, -32 * 8);
            scroll = Point(0, -32 * 9);
        }
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
                    std::string msg_data = "ドウカ、ツナガッテクダサイ";
                    auto msg_view = MessageView::create(msg_data);
                    view->addChild(msg_view);
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