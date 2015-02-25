//
//  MakeMenuControllerLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/2/25.
//
//

#include "MakeMenuControllerLayer.h"
#include "MenuDecideItem.h"

USING_NS_CC;

bool MakeMenuControllerLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }

    auto decide_button = MenuDecideItem::create();
    decide_button->setPosition(100, 80);
    
    auto decide_menu = Menu::create(decide_button, nullptr);
    decide_menu->setPosition(Point::ZERO);
    addChild(decide_menu);

    return true;
}
