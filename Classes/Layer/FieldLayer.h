//
//  FieldLayer.h
//  solno
//
//  Created by S_Wyvern on 2014/12/26.
//
//

#ifndef __solno__FieldLayer__
#define __solno__FieldLayer__

#include <stdio.h>
#include <cocos2d.h>

enum PlayerActionTags {
    MOVE_SEQUENCE = 11,
};

class FieldLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(FieldLayer);
    void changePlayerAnimation(std::string direction);
    bool runMoveAction(cocos2d::Point move_vec);
    virtual void update(float dt);

private:
    cocos2d::Sprite* player_sprite;
    cocos2d::Animate* player_idling_animate;
};

#endif /* defined(__solno__FieldLayer__) */
