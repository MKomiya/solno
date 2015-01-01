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

FieldState::FieldState(FieldLayer* view, TMXLayer* collider) :
_view(view),
_player_map_pos(Point(0, 0)),
_player_direction("down"),
_map_collider(collider)
{
}

FieldState::~FieldState()
{
}

void FieldState::update()
{
    CCLOG("FieldState: update");
    
    auto command = InputModule::getInstance()->getInputCommand();
    if (command != InputCommand::NOTHING) {
        _movePlayerCharacter(command);
    }
}

void FieldState::_movePlayerCharacter(InputCommand move_command)
{
    std::string direction_str;
    
    auto move_vec = Point(0, 0);
    auto next_pos = _player_map_pos;
    if (move_command == InputCommand::MOVE_UP) {
        direction_str = "up";
        move_vec.y = 32;
        next_pos.y -= 1;
    } else if (move_command == InputCommand::MOVE_LEFT) {
        direction_str = "left";
        move_vec.x = -32;
        next_pos.x -= 1;
    } else if (move_command == InputCommand::MOVE_DOWN) {
        direction_str = "down";
        move_vec.y = -32;
        next_pos.y += 1;
    } else if (move_command == InputCommand::MOVE_RIGHT) {
        direction_str = "right";
        move_vec.x = 32;
        next_pos.x += 1;
    }
    
    if (_player_direction != direction_str) {
        _view->changePlayerAnimation(direction_str);
        _player_direction = direction_str;
    }
    
    // check collidable
    if (this->_isCollidable(next_pos.x, next_pos.y)) {
        return ;
    }
    
    // run move action
    if (_view->runMoveAction(move_vec)) {
        _player_map_pos = next_pos; // move successful
    }
}

bool FieldState::_isCollidable(int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0) {
        return false;
    }
    
    auto tiled_gid = _map_collider->getTileGIDAt(Point(map_x, map_y));
    
    if (tiled_gid == MapColliderType::COLLIDABLE) {
        return true;
    }
    
    return false;
}