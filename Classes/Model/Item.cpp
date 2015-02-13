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
        ret->setItemId(999);
        ret->setType(ItemType::OPERATE_OBJECT);
        ret->setItemName("モックアイテム");
        ret->setPrepareItemId1(999);
        ret->setPrepareItemId2(999);
        ret->setPrepareItemId3(999);
        
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
    auto data   = master->getOne(item_id);
    
    auto type   = data.type;
    if (type == ItemType::OPERATE_OBJECT || ItemType::MATERIAL_ITEM) {
        auto ret = new ObjectOperateItem();
        if (!ret) {
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
        
        ret->setId(1);
        ret->setItemId(item_id);
        ret->setType(type);
        ret->setItemName(data.name);
        ret->setPrepareItemId1(data.prepare_item_1_id);
        ret->setPrepareItemId2(data.prepare_item_2_id);
        ret->setPrepareItemId3(data.prepare_item_3_id);
        
        auto path = "item/" + std::to_string(item_id) + ".png";
        auto tc = Director::getInstance()->getTextureCache();
        auto texture = tc->addImage(path);
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
    
    auto prepare_item_id  = prepare_item_ids.front();
    auto make_item = Item::createByMaster(prepare_item_id);
    
    return make_item;
}