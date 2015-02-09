//
//  ItemMenuState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "ItemMenuState.h"
#include "FieldState.h"
#include "StateMachineModule.h"
#include "Item.h"
#include "MasterStorageModule.h"
#include "InputModule.h"

#include "ItemMenuLayer.h"
#include "LayerManager.h"

ItemMenuState* ItemMenuState::create()
{
    auto ret = new ItemMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->setCurrentItemIndex(0);
    ret->autorelease();
    return ret;
}

void ItemMenuState::enter()
{
    // repositoryからitem list読込
    // add test data
    for (int i=0; i < 10; ++i) {
        item_list.pushBack(Item::create(i+1, 3, Item::ItemType::OPERATE_OBJECT));
    }
    
    // ItemMenuLayerへset
    auto view = ItemMenuLayer::create(item_list);
    LayerManager::getInstance()->push("item_menu", view);
}

void ItemMenuState::update()
{
    auto e = InputModule::getInstance()->popEvent();
    auto p = InputModule::getInstance()->popParam();
    
    if (e == InputEvent::PRESS_ITEM_SELECT) {
        if (p < 0 || p >= item_list.size()) {
            return ;
        }
        
        if (current_item_idx != p) {
            current_item_idx = p;
            return ;
        }
        
        auto item = item_list.at(p);
        
        auto fsm = StateMachineModule::getInstance();
        FieldState* field_state = (FieldState*)fsm->getState("field");
        field_state->addExecuteItem(item);
        fsm->changeState("field");
        return ;
    }
    
    if (e == InputEvent::RELEASE_DECIDE) {
        if (p < 0 || p >= item_list.size()) {
            return ;
        }
        
        auto item = item_list.at(p);
        
        auto fsm = StateMachineModule::getInstance();
        FieldState* field_state = (FieldState*)fsm->getState("field");
        field_state->addExecuteItem(item);
        fsm->changeState("field");
        return ;
    }
}

void ItemMenuState::exit()
{
    LayerManager::getInstance()->pop();
}

MakeTreeData ItemMenuState::updateMakeTreeData()
{
    int idx = 3;
    
    auto master = MasterStorageModule::getInstance();
    auto current_item  = item_list.at(idx);
    auto make_item_ids = master->findPrepareItemIdsByItemId(current_item->getItemId());
    auto make_item_id  = make_item_ids.front().int_value();
    auto make_item     = Item::createByMaster(make_item_id);
    
    std::vector<int> preparent_item_ids;
    preparent_item_ids.push_back(make_item->getPrepareItemId1());
    preparent_item_ids.push_back(make_item->getPrepareItemId2());
    preparent_item_ids.push_back(make_item->getPrepareItemId3());
    
    auto it = std::remove_if(preparent_item_ids.begin(), preparent_item_ids.end(), [current_item](int v) -> bool{
        return v == current_item->getItemId();
    });
    preparent_item_ids.erase(it, preparent_item_ids.end());
    
    std::vector<Item*> preparent_items;
    preparent_items.push_back(current_item);
    
    // いちいちItem Model作らずともTextureだけとれればよさそう
    for (auto preparent_item_id : preparent_item_ids) {
        auto item = Item::createByMaster(preparent_item_id);
        preparent_items.push_back(item);
    }
    
    MakeTreeData ret;
    ret.prepare_items = preparent_items;
    ret.make_item     = make_item;
    
    return ret;
}