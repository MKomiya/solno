//
//  ItemMenuState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "ItemMenuState.h"
#include "FieldState.h"
#include "Item.h"
#include "MasterStorageModule.h"
#include "UserStorageModule.h"
#include "Dispatcher.h"
#include "ViewManager.h"

#include "ItemMenuLayer.h"
#include "Router.h"

ItemMenuState* ItemMenuState::create()
{
    auto ret = new ItemMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->init();
    ret->setCurrentItemIndex(0);
    ret->autorelease();
    return ret;
}

void ItemMenuState::enter()
{
    Raciela::State::enter();
    
    // repositoryからitem list読込
    auto user_item_list = UserStorageModule::getInstance()->getAllUserItem();
    for (auto user_item : user_item_list) {
        auto item = Item::createByMaster(user_item.item_id);
        item_list.pushBack(item);
    }
    
    // ItemMenuLayerへset
    view = ItemMenuLayer::create(item_list);
    auto view_manager = Raciela::ViewManager::getInstance();
    view_manager->addView(view);
}

void ItemMenuState::update()
{
}

void ItemMenuState::exit()
{
    Raciela::State::exit();
    
    item_list.clear();
    Raciela::ViewManager::getInstance()->removeView(view);
}

void ItemMenuState::delegate()
{
    dispatcher->subscribe<void (int)>("selected_item", [=](int index) {
        if (index < 0 || index >= item_list.size()) {
            return ;
        }
        
        auto item = item_list.at(index);
        if (current_item_idx != index) {
            current_item_idx = index;
            // view->updateMakeTreeView(current_item);
            return ;
        }
        
        dispatcher->dispatch_transition("use_item", item);
        Raciela::Router::getInstance()->popState();
    });
}
