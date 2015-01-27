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
}

void ItemMenuState::update()
{
    
}

void ItemMenuState::exit()
{
    
}