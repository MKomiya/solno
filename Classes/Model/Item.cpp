//
//  Item.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "Item.h"

Item* Item::create()
{
    auto ret = new Item();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return ret;
    }
    return ret;
}