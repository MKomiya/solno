//
//  ControllerLayer.h
//  solno
//
//  Created by S_Wyvern on 2014/12/27.
//
//

#ifndef __solno__ControllerLayer__
#define __solno__ControllerLayer__

#include <stdio.h>
#include <cocos2d.h>

class ControllerLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ControllerLayer);
};

#endif /* defined(__solno__ControllerLayer__) */
