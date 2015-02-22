//
//  Direction.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/12.
//
//

#include "Direction.h"
#include "MenuArrowItem.h"

USING_NS_CC;

Direction Direction::createInstance(ArrowInputEvent event)
{
    Direction ret;
    if (event == ArrowInputEvent::PRESS_DOWN) {
        ret.vec = Vec2(0, -1);
        ret.str = "down";
    } else if (event == ArrowInputEvent::PRESS_LEFT) {
        ret.vec = Vec2(-1, 0);
        ret.str = "left";
    } else if (event == ArrowInputEvent::PRESS_RIGHT) {
        ret.vec = Vec2(1, 0);
        ret.str = "right";
    } else if (event == ArrowInputEvent::PRESS_UP) {
        ret.vec = Vec2(0, 1);
        ret.str = "up";
    }
    return ret;
}

Direction Direction::createInstance(std::string direction_str)
{
    Direction ret;
    ret.str = direction_str;
    if (ret.str == "down") {
        ret.vec = Vec2(0, -1);
    } else if (ret.str == "left") {
        ret.vec = Vec2(-1, 0);
    } else if (ret.str == "right") {
        ret.vec = Vec2(1, 0);
    } else if (ret.str == "up") {
        ret.vec = Vec2(0, 1);
    }
    return ret;
}