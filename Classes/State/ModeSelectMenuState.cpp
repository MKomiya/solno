//
//  ModeSelectMenuState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#include "ModeSelectMenuState.h"
#include "StateMachineModule.h"

#include "LayerManager.h"
#include "ModeSelectMenuLayer.h"

#include "InputModule.h"
#include "Dispatcher.h"
#include "Router.h"

#include "ItemMenuState.h"
#include "MakeMenuState.h"

USING_NS_CC;

ModeSelectMenuState* ModeSelectMenuState::create()
{
    auto ret = new ModeSelectMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->autorelease();
    return ret;
}

void ModeSelectMenuState::enter()
{
    view = ModeSelectMenuLayer::create();
    LayerManager::getInstance()->push("mode_select_menu", view);
}

void ModeSelectMenuState::update()
{
    auto event = InputModule::getInstance()->popEvent();
    
    if (event == InputEvent::PRESS_MODE_SELECT_ITEM) {
        StateMachineModule::getInstance()->changeState("item_menu");
    } else if (event == InputEvent::PRESS_MODE_SELECT_MAKE) {
        StateMachineModule::getInstance()->changeState("make_menu");
    }
}

void ModeSelectMenuState::exit()
{
    LayerManager::getInstance()->pop();
}

void ModeSelectMenuState::delegate()
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    
    dispatcher->subscribe<void ()>("selected_item", [=]() {
    });
    
    dispatcher->subscribe<void ()>("selected_make", [=]() {
    });
}