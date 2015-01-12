//
//  Direction.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/12.
//
//

#include "Direction.h"

USING_NS_CC;

Direction Direction::createInstance(InputEvent event)
{
    Direction ret;
    if (event == InputEvent::PRESS_DOWN) {
        ret.vec = Vec2(0, -1);
        ret.str = "down";
    } else if (event == InputEvent::PRESS_LEFT) {
        ret.vec = Vec2(-1, 0);
        ret.str = "left";
    } else if (event == InputEvent::PRESS_RIGHT) {
        ret.vec = Vec2(1, 0);
        ret.str = "right";
    } else if (event == InputEvent::PRESS_UP) {
        ret.vec = Vec2(0, 1);
        ret.str = "up";
    }
    return ret;
}