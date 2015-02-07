//
//  Item.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "Item.h"

#include "ObjectOperateItem.h"

#pragma mark create method
Item* Item::create(int id, int item_id, int type)
{
    if (type == ItemType::OPERATE_OBJECT) {
        auto ret = new ObjectOperateItem();
        if (!ret) {
            CC_SAFE_DELETE(ret);
            return ret;
        }
        
        ret->setId(id);
        ret->setItemId(item_id);
        ret->setType(type);
        ret->setItemName("プラグイン：オノ");
        return ret;
    }
    
    return nullptr;
}

#pragma mark override method
void Item::useItem()
{
}