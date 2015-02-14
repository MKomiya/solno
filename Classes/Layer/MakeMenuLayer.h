//
//  MakeMenuLayer.h
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#ifndef __solno__MakeMenuLayer__
#define __solno__MakeMenuLayer__

#include <iostream>
#include <cocos2d.h>

#include "Item.h"

class MakeMenuLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MakeMenuLayer);

private:
    cocos2d::Sprite* current_cursor;
};

#endif /* defined(__solno__MakeMenuLayer__) */
