//
//  OpeningState.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#include "OpeningState.h"
#include "OpeningLayer.h"
#include "Router.h"
#include "Dispatcher.h"

USING_NS_CC;

OpeningState* OpeningState::create()
{
    auto ret = new OpeningState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    
    ret->init();
    ret->autorelease();
    ret->created();
    return ret;
}

void OpeningState::enter()
{
    view = OpeningLayer::create();
    auto router = Raciela::Router::getInstance();
    router->addView(view);
}

void OpeningState::update()
{
    
}

void OpeningState::exit()
{
    Raciela::Router::getInstance()->removeView(view);
}

void OpeningState::delegate()
{
    dispatcher->subscribe<void ()>("touched", [=]() {
        view->nextMessages();
    });
}