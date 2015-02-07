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

#include "ItemMenuLayer.h"
#include "LayerManager.h"

#include "InputModule.h"

#include "Item.h"

ItemMenuState* ItemMenuState::create()
{
    auto ret = new ItemMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
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
        
        auto item = item_list.at(p);
        
        auto fsm = StateMachineModule::getInstance();
        FieldState* field_state = (FieldState*)fsm->getState("field");
        field_state->addExecuteItem(item);
        fsm->changeState("field");
    }
}

void ItemMenuState::exit()
{
    LayerManager::getInstance()->pop();
}