//
//  Item.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "Item.h"
#include "ObjectOperateItem.h"
#include "MaterialItem.h"

#include "MasterStorageModule.h"
#include "UserStorageModule.h"

USING_NS_CC;

#pragma mark create method
Item::Item(int id, int item_id)
{
    auto master = MasterStorageModule::getInstance();
    auto data   = master->getOne(item_id);
    
    setId(id);
    setItemId(item_id);
    setType(data.type);
    setItemName(data.name);
    setPrepareItemId1(data.preparent_item_1_id);
    setPrepareItemId2(data.preparent_item_2_id);
    setPrepareItemId3(data.preparent_item_3_id);
    
    auto path = "item/" + std::to_string(item_id) + ".png";
    auto tc = Director::getInstance()->getTextureCache();
    auto texture = tc->addImage(path);
    setThumbnailTexture(texture);
}

Item* Item::createByMaster(int item_id)
{
    auto master = MasterStorageModule::getInstance();
    auto data   = master->getOne(item_id);
    
    switch (data.type) {
        case ItemType::OPERATE_OBJECT:
            return new ObjectOperateItem(1, item_id);
        case ItemType::MATERIAL_ITEM:
            return new MaterialItem(1, item_id);
    }
    
    return nullptr;
}

#pragma mark override method
void Item::useItem(FieldState *state)
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
    
    if (prepare_item_id == 0) {
        return nullptr;
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
