//
//  ItemMenuLayer.h
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#ifndef __solno__ItemMenuLayer__
#define __solno__ItemMenuLayer__

#include <stdio.h>
#include <cocos2d.h>

#include "Item.h"

class ItemMenuLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(ItemMenuLayer);
    
    CC_SYNTHESIZE(cocos2d::Vector<Item*>, item_list, ItemList);
};

#endif /* defined(__solno__ItemMenuLayer__) */
