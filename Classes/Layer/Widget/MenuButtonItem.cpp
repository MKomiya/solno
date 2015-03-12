//
//  MenuButtonItem.cpp
//  solno
//
//  Created by S_Wyvern on 2015/02/28.
//
//

#include "MenuButtonItem.h"
#include "Dispatcher.h"

USING_NS_CC;

MenuButtonItem* MenuButtonItem::create()
{
    auto ret = new MenuButtonItem();
    auto s = Sprite::create("ui/ui_menu_button.png");
    if (ret && ret->initWithNormalSprite(s, s, s, nullptr)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void MenuButtonItem::selected()
{
    MenuItemSprite::selected();
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("press_menu");
}

void MenuButtonItem::unselected()
{
    MenuItemSprite::unselected();
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("release_menu");
}