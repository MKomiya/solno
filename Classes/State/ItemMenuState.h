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
#include "State.h"

class Item;

class ItemMenuState : public Raciela::State
{
public:
    static ItemMenuState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;
    
    CC_SYNTHESIZE(int, current_item_idx, CurrentItemIndex);
    
private:
    cocos2d::Vector<Item*> item_list;
};

#endif /* defined(__solno__ItemMenuState__) */
