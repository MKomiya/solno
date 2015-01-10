//
//  PlayerView.h
//  solno
//
//  Created by S_Wyvern on 2015/01/05.
//
//

#ifndef __solno__PlayerView__
#define __solno__PlayerView__

#include <stdio.h>
#include <cocos2d.h>

class PlayerView : public cocos2d::Sprite
{
public:
    enum PlayerActionTag {
        IDLING_ANIMATE,
        MOVE_SEQUENCE,
    };
    
    static PlayerView* create();
    void setIdlingAnimate(std::string direction);
    void runMoveAction(cocos2d::Point move_vec);
    bool isRunnningMoveAction();
    void addRunActionAfterMove(cocos2d::FiniteTimeAction* action);
    
private:
    cocos2d::Vector<cocos2d::FiniteTimeAction*> after_move_action;
};

#endif /* defined(__solno__PlayerView__) */
