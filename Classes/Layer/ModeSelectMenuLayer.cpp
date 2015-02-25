//
//  ModeSelectMenuLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/27.
//
//

#include "ModeSelectMenuLayer.h"

#include "Dispatcher.h"

USING_NS_CC;

bool ModeSelectMenuLayer::init()
{
    if (!Raciela::View::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto item_label = Label::createWithBMFont("fonts/message_font.fnt", "ITEM");
    item_label->getTexture()->setAliasTexParameters();
    
    auto menu_item = MenuItemLabel::create(item_label);
    menu_item->setScale(3.0f);
    menu_item->setPosition(Point(s.width / 2.0f, s.height * 3.0f / 4.0f));
    menu_item->setCallback([=](Ref* sender) {
        auto dispatcher = Raciela::Dispatcher::getInstance();
        dispatcher->dispatch("selected_item");
    });
    
    auto make_label = Label::createWithBMFont("fonts/message_font.fnt", "MAKE");
    make_label->getTexture()->setAliasTexParameters();
    
    auto menu_make = MenuItemLabel::create(make_label);
    menu_make->setScale(3.0f);
    menu_make->setPosition(Point(s.width / 2.0f, s.height * 2.5f / 4.0f));
    menu_make->setCallback([=](Ref* sender) {
        auto dispatcher = Raciela::Dispatcher::getInstance();
        dispatcher->dispatch("selected_make");
    });
    
    auto menu = Menu::create(menu_item, menu_make, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    return true;
}