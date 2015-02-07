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

struct MakeTreeData {
    std::vector<Item*> prepare_items;
    Item* make_item;
};

class ItemMenuState : public StateBase
{
public:
    static ItemMenuState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    
    MakeTreeData updateMakeTreeData();
    
private:
    cocos2d::Vector<Item*> item_list;
};

#endif /* defined(__solno__ItemMenuState__) */
