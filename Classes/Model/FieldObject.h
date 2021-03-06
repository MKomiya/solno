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
class FieldState;
class FieldObject : public cocos2d::Ref
{
public:
    enum ObjectType {
        MOVABLE_ROCK  = 1, // 動かせる岩
        MESSAGE_POINT = 2, // 会話が流れるポイント
        START_POINT   = 3, // スタート地点
        TREE          = 4, // 破壊出来る木
        STORY_POINT   = 5, // 回想ポイント
    };
    
    FieldObject(FieldState* state, int id, cocos2d::ValueMap data);
    
    static FieldObject* create(FieldState* state, int id, cocos2d::ValueMap data);
    
    virtual void executePreMoveAction(Direction);
    virtual void executeDecideAction();
    virtual void executeMovedAction();
    virtual bool isPassablePlayer();
    virtual int getBreakItemId();
    
    CC_SYNTHESIZE(int, id, Id);
    CC_SYNTHESIZE(cocos2d::Point, pos, Position);
    CC_SYNTHESIZE(ObjectType, obj_type, ObjectType);
    CC_SYNTHESIZE(FieldState*, state, FieldState);
};

#endif /* defined(__solno__FieldObject__) */
