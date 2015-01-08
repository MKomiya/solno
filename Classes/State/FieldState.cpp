//
//  FieldState.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "FieldState.h"

#include "FieldLayer.h"

USING_NS_CC;

FieldState::FieldState(FieldLayer* view) :
player_map_pos(Point(0, 0)),
player_direction("down"),
view(view)
{
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
    
    // check collidable
    if (isCollidable(next_pos.x, next_pos.y)) {
        return ;
    }
    
    // update player position
    player_map_pos = next_pos;
    CCLOG("moved pos(%f, %f)", player_map_pos.x, player_map_pos.y);
    
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
}

bool FieldState::isCollidable(int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0) {
        return false;
    }
    
    auto tiled_gid = view->getMapCollider()->getTileGIDAt(Point(map_x, map_y));
    
    if (tiled_gid == MapColliderType::COLLIDABLE) {
        return true;
    }
    
    return false;
}