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

#include "InputModule.h"

enum MapColliderType {
    NO_COLLISION = 0,
    COLLIDABLE   = 17, // タイルが増えるとGIDが変わるので別途検討
};
enum ObjectType {
    MOVABLE_ROCK = 1,
};
struct FieldObject {
    int id;
    cocos2d::Point pos;
    ObjectType type;
    
    FieldObject(int i, cocos2d::Point p, ObjectType t) {
        id   = i;
        pos  = p;
        type = t;
    }
};

class FieldLayer;
class FieldState : public IState {
public:
    FieldState(FieldLayer* view);
    virtual ~FieldState();
    virtual void update();
    
private:
    void movePlayerCharacter(InputEvent event);
    bool isCollidable(int map_x, int map_y);
    
    cocos2d::Point player_map_pos;
    std::string player_direction;
    FieldLayer* view;
    std::vector<FieldObject*> objects;
};

#endif /* defined(__solno__FieldState__) */
