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

class FieldLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(FieldLayer);
    
private:
    void _changePlayerAnimation(std::string direction);
    
    cocos2d::Animate* player_idling_animate;
};

#endif /* defined(__solno__FieldLayer__) */
