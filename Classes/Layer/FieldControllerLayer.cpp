//
//  FieldControllerLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/2/26.
//
//

#include "FieldControllerLayer.h"
#include "MenuArrowItem.h"
#include "MenuDecideItem.h"
#include "MenuButtonItem.h"

USING_NS_CC;

bool FieldControllerLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    auto button = MenuArrowItem::create("up");
    button->setPosition(230, 117);
    auto button2 = MenuArrowItem::create("left");
    button2->setPosition(191, 82);
    auto button3 = MenuArrowItem::create("down");
    button3->setPosition(230, 48);
    auto button4 = MenuArrowItem::create("right");
    button4->setPosition(269, 82);
    
    auto decide_button = MenuDecideItem::create();
    decide_button->setPosition(100, 80);
    
    arrow_menu = Menu::create(button, button2, button3, button4, NULL);
    arrow_menu->setPosition(Point::ZERO);
    addChild(arrow_menu);
    
    auto menu_button = MenuButtonItem::create();
    menu_button->setPosition(50, 60);
    
    auto decide_menu = Menu::create(decide_button, menu_button, nullptr);
    decide_menu->setPosition(Point::ZERO);
    addChild(decide_menu);
    
    return true;
}

void FieldControllerLayer::setEnableArrowButtons(bool enabled)
{
    arrow_menu->setEnabled(enabled);
}