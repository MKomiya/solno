//
//  Item.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "Item.h"

#pragma mark create method
Item* Item::create(int id, int item_id, int type)
{
    auto ret = new Item();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return ret;
    }

    ret->setId(id);
    ret->setItemId(item_id);
    ret->setType(type);
    return ret;
}

#pragma mark override method
void Item::useItem()
{
}