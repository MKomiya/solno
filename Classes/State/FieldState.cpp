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
    CCLOG("FieldState: update");
    
    auto event = InputModule::getInstance()->popEvent();
    if (event != 0) {
        movePlayerCharacter(event);
    }
}

void FieldState::movePlayerCharacter(InputEvent event)
{
    std::string direction_str;
    
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
    
    std::string ret = "";
    if (player_direction != direction_str) {
        player_direction = direction_str;
        ret = direction_str;
    }
    
    // check collidable
    if (isCollidable(next_pos.x, next_pos.y)) {
        return ;
    }
    
    // run move action
    if (view->runMoveAction(move_vec, ret)) {
        player_map_pos = next_pos;
    }
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