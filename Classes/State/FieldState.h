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
    FieldState();
    virtual ~FieldState();
    virtual void update();
    
private:
    void movePlayerCharacter(InputEvent event);
    bool isCollidable(int map_x, int map_y);
    
    cocos2d::Point player_map_pos;
    std::string player_direction;
    FieldLayer* view;
};

#endif /* defined(__solno__FieldState__) */
