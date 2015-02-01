//
//  ItemMenuState.h
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#ifndef __solno__ItemMenuState__
#define __solno__ItemMenuState__

#include <stdio.h>
#include "StateBase.h"

class Item;
class ItemMenuState : public StateBase
{
public:
    static ItemMenuState* create();
    
    virtual void enter(int gate) override;
    virtual void update() override;
    virtual void exit() override;
    
private:
    cocos2d::Vector<Item*> item_list;
};

#endif /* defined(__solno__ItemMenuState__) */
