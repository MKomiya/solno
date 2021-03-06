//
//  MenuDecideItem.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/11.
//
//

#include "MenuDecideItem.h"
#include "Dispatcher.h"

USING_NS_CC;

MenuDecideItem* MenuDecideItem::create()
{
    auto ret = new MenuDecideItem();
    auto s = Sprite::create("ui/ui_decide_button.png");
    if (ret && ret->initWithNormalSprite(s, s, s, nullptr)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void MenuDecideItem::selected()
{
    MenuItemSprite::selected();
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("press_decide");
}

void MenuDecideItem::unselected()
{
    MenuItemSprite::unselected();
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("release_decide");
}