//
//  FieldState.h
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#ifndef __solno__FieldState__
#define __solno__FieldState__

#include <stdio.h>
#include <cocos2d.h>

#include "IState.h"
#include "FieldState.h"

#include "InputModule.h"

enum MapColliderType {
    NO_COLLISION = 0,
    COLLIDABLE   = 14,
};

class FieldLayer;
class FieldState : public IState {
public:
    FieldState(FieldLayer* view, cocos2d::TMXLayer* collider);
    virtual ~FieldState();
    virtual void update();
    
private:
    void _movePlayerCharacter(InputCommand move_command);
    bool _isCollidable(int map_x, int map_y);
    
    FieldLayer* _view;
    cocos2d::Point _player_map_pos;
    std::string _player_direction;
    cocos2d::TMXLayer* _map_collider;
};

#endif /* defined(__solno__FieldState__) */
