//
//  FieldObject.h
//  solno
//
//  Created by S_Wyvern on 2015/01/21.
//
//

#ifndef __solno__FieldObject__
#define __solno__FieldObject__

#include <stdio.h>
#include <cocos2d.h>

class Direction;
class FieldLayer;
class FieldObject : public cocos2d::Ref
{
public:
    static FieldObject* create(int id, cocos2d::Point pos, std::string type_str, std::string optional_params);
    
    virtual void executePreMoveAction(Direction, FieldLayer*);
    virtual void executeMovedAction(FieldLayer*);
    
    CC_SYNTHESIZE(int, id, Id);
    CC_SYNTHESIZE(cocos2d::Point, pos, Position);
    CC_SYNTHESIZE(std::string, optional_params, OptionalParams);
};

#endif /* defined(__solno__FieldObject__) */
