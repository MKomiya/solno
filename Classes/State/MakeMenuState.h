//
//  MakeMenuState.h
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#ifndef __solno__MakeMenuState__
#define __solno__MakeMenuState__

#include <iostream>
#include "State.h"

#include "Item.h"

class MakeMenuLayer;
class MakeMenuControllerLayer;
class MakeMenuState : public Raciela::State
{
public:
    static MakeMenuState* create();
    
    virtual void enter() override;
    virtual void update() override;
    virtual void exit() override;
    virtual void delegate() override;
    
    void updatePreparentItem(Item* item);
    
    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<Item*>, item_list, ItemList);
    CC_SYNTHESIZE_PASS_BY_REF(std::vector<int>, preparent_item_ids, PreparentItemList);
    CC_SYNTHESIZE_READONLY(MakeMenuLayer*, view, View);
    CC_SYNTHESIZE_READONLY(MakeMenuControllerLayer*, controller, Controller);
    CC_SYNTHESIZE(int, current_item_idx, CurrentItemIndex);
    CC_SYNTHESIZE(Item*, make_item, MakeItem);
private:
    bool canMakeItem(const Item* make_item, const std::vector<int> selected_item_ids);
};

#endif /* defined(__solno__MakeMenuState__) */
