//
//  Item.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "Item.h"
#include "ObjectOperateItem.h"

#include "MasterStorageModule.h"

#pragma mark create method
Item* Item::create(int id, int item_id, int type)
{
    if (type == ItemType::OPERATE_OBJECT) {
        auto ret = new ObjectOperateItem();
        if (!ret) {
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        ret->setId(id);
        ret->setItemId(item_id);
        ret->setType(type);
        ret->setItemName("プラグイン：オノ");
        return ret;
    }
    
    return nullptr;
}

Item* Item::createByMaster(int item_id)
{
    auto master = MasterStorageModule::getInstance();
    auto data   = master->getOne(MasterStorageModule::MASTER_NS_ITEM, item_id);
    
    auto type   = data["type"].int_value();
    if (type == ItemType::OPERATE_OBJECT) {
        auto ret = new ObjectOperateItem();
        if (!ret) {
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        ret->setId(1);
        ret->setItemId(item_id);
        ret->setType(type);
        ret->setItemName(data["name"].string_value());
        ret->setPrepareItemId1(data["preparent_item_1_id"].int_value());
        ret->setPrepareItemId2(data["preparent_item_2_id"].int_value());
        ret->setPrepareItemId3(data["preparent_item_3_id"].int_value());
        return ret;
    }
}

#pragma mark override method
void Item::useItem()
{
}