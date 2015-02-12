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
#include "UserStorageModule.h"
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
    auto user_item_list = UserStorageModule::getInstance()->getAllUserItem();
    for (auto user_item : user_item_list) {
        auto item = Item::createByMaster(user_item.item_id);
        item_list.pushBack(item);
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
        
        auto item = item_list.at(p);
        if (current_item_idx != p) {
            current_item_idx = p;
            
            // view->updateMakeTreeView(current_item);
            
            return ;
        }
        
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
    item_list.clear();
    LayerManager::getInstance()->pop();
}