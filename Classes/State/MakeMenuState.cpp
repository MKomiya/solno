//
//  MakeMenuState.cpp
//  solno
//
//  Created by Mitsushige Komiya on 2015/01/29.
//
//

#include "MakeMenuState.h"
#include "MakeMenuLayer.h"
#include "LayerManager.h"

MakeMenuState* MakeMenuState::create()
{
    auto ret = new MakeMenuState();
    if (!ret) {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
    ret->autorelease();
    return ret;
}

void MakeMenuState::enter()
{
    auto view = MakeMenuLayer::create();
    LayerManager::getInstance()->push("make_menu", view);
}

void MakeMenuState::update()
{
    
}

void MakeMenuState::exit()
{
    LayerManager::getInstance()->pop();
}