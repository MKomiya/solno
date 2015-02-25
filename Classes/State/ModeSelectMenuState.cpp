//
//  ModeSelectMenuState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#include "ModeSelectMenuState.h"

#include "Router.h"
#include "ModeSelectMenuLayer.h"

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
    
    ret->init();
    ret->autorelease();
    ret->created();
    return ret;
}

void ModeSelectMenuState::enter()
{
    view = ModeSelectMenuLayer::create();
    auto router = Raciela::Router::getInstance();
    router->addView(view);
}

void ModeSelectMenuState::update()
{
}

void ModeSelectMenuState::exit()
{
    Raciela::Router::getInstance()->removeView(view);
}

void ModeSelectMenuState::delegate()
{
    auto dispatcher = Raciela::Dispatcher::getInstance();
    
    dispatcher->subscribe<void ()>("selected_item", [=]() {
        auto router = Raciela::Router::getInstance();
        router->popState();
        router->pushState(ItemMenuState::create());
    });
    
    dispatcher->subscribe<void ()>("selected_make", [=]() {
        auto router = Raciela::Router::getInstance();
        router->popState();
        router->pushState(MakeMenuState::create());
    });
}