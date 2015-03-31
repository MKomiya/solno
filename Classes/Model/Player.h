//
//  Player.h
//  solno
//
//  Created by Mitsushige Komiya on 2015/03/31.
//
//

#ifndef __solno__Player__
#define __solno__Player__

#include <iostream>
#include <cocos2d.h>
#include "json11.hpp"

class Player
{
public:
    int map_x, map_y;
    
    Player(cocos2d::Point pos) :
    map_x(pos.x),map_y(pos.y) {}
    
    json11::Json to_json() const
    {
        return json11::Json::object {
            { "map_x", map_x },
            { "map_y", map_y }
        };
    }
};

#endif /* defined(__solno__Player__) */
