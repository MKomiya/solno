//
//  Direction.h
//  solno
//
//  Created by S_Wyvern on 2015/01/12.
//
//

#ifndef __solno__Direction__
#define __solno__Direction__

#include <stdio.h>
#include <cocos2d.h>

enum class ArrowInputEvent;

class Direction
{
public:
    static Direction createInstance(ArrowInputEvent event);
    static Direction createInstance(std::string direction_str);
    inline cocos2d::Vec2 getUnitVec() const {
        return vec;
    }
    inline cocos2d::Vec2 getMapPointVec() const {
        return cocos2d::Vec2(vec.x, -1 * vec.y);
    }
    inline std::string getDirectionLabel() const {
        return str;
    }
    
private:
    cocos2d::Vec2 vec;
    std::string str;
};

#endif /* defined(__solno__Direction__) */
