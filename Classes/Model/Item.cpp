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

USING_NS_CC;

#pragma mark create method
Item* Item::createMock(int id)
{
    if (true) {
        auto ret = new ObjectOperateItem();
        if (!ret) {
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        ret->setId(id);
        ret->setItemId(3);
        ret->setType(ItemType::OPERATE_OBJECT);
        ret->setItemName("プラグイン：オノ");
        ret->setPrepareItemId1(3);
        ret->setPrepareItemId2(3);
        ret->setPrepareItemId3(3);
        
        auto tc = Director::getInstance()->getTextureCache();
        auto texture = tc->addImage("item/1.png");
        ret->setThumbnailTexture(texture);
        return ret;
    }
    
    return nullptr;
}

Item* Item::createByMaster(int item_id)
{
    auto master = MasterStorageModule::getInstance();
    auto data   = master->getOne(MasterStorageModule::MASTER_NS_ITEM, item_id);
    
    auto type   = data["type"].int_value();
    if (type == ItemType::OPERATE_OBJECT || ItemType::MATERIAL_ITEM) {
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
        
        auto tc = Director::getInstance()->getTextureCache();
        auto texture = tc->addImage("item/1.png");
        ret->setThumbnailTexture(texture);
        return ret;
    }
    
    return nullptr;
}

#pragma mark override method
void Item::useItem()
{
}

#pragma mark getter method
Texture2D* Item::getPrepareItemTexture(int prepare_index)
{
    int prepare_item_id;
    if (prepare_index == 1) {
        prepare_item_id = prepare_item_id_1;
    } else if (prepare_index == 2) {
        prepare_item_id = prepare_item_id_2;
    } else if (prepare_index == 3) {
        prepare_item_id = prepare_item_id_3;
    } else {
        throw "Invalid prepare item index";
    }
    
    auto prepare_item = Item::createByMaster(prepare_item_id);
    return prepare_item->getThumbnailTexture();
}

Item* Item::getMakeItem()
{
    auto master           = MasterStorageModule::getInstance();
    auto prepare_item_ids = master->findPrepareItemIdsByItemId(item_id);
    if (prepare_item_ids.size() == 0) {
        return nullptr;
    }
    
    auto prepare_item_id  = prepare_item_ids.front().int_value();
    auto make_item = Item::createByMaster(prepare_item_id);
    
    return make_item;
}