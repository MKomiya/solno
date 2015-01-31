//
//  ItemMenuState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "ItemMenuState.h"

#include "ItemMenuLayer.h"
#include "LayerManager.h"

#include "InputModule.h"

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
    
    // ItemMenuLayerへset
    auto view = ItemMenuLayer::create();
    LayerManager::getInstance()->push("item_menu", view);
}

void ItemMenuState::update()
{
    auto e = InputModule::getInstance()->popEvent();
    auto p = InputModule::getInstance()->popParam();
    
    if (e == InputEvent::PRESS_ITEM_SELECT) {
        CCLOG("アイテム選択：%d", p);
    }
}

void ItemMenuState::exit()
{
    LayerManager::getInstance()->pop();
}