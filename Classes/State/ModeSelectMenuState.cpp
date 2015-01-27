//
//  ModeSelectMenuState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#include "ModeSelectMenuState.h"

#include "LayerManager.h"
#include "ModeSelectMenuLayer.h"

USING_NS_CC;

ModeSelectMenuState* ModeSelectMenuState::create()
{
    auto ret = new ModeSelectMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    return ret;
}

void ModeSelectMenuState::enter()
{
    view = ModeSelectMenuLayer::create();
    LayerManager::getInstance()->push("mode_select_menu", view);
}

void ModeSelectMenuState::update()
{
    /*
    auto event = InputModule::getInstance()->popEvent();
    
    if (event == InputEvent::RELEASE_DECIDE) {
        // アイテムステート発行
        auto next_state = ItemState::create();
        StateMachineModule::getInstance()->changeState("item_menu");
    }
    */
}

void ModeSelectMenuState::exit()
{
    LayerManager::getInstance()->pop();
}