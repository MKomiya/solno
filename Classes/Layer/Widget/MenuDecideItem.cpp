//
//  MenuDecideItem.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/11.
//
//

#include "MenuDecideItem.h"
#include "InputModule.h"

USING_NS_CC;

MenuDecideItem* MenuDecideItem::create()
{
    auto ret = new MenuDecideItem();
    if (ret && ret->initWithString("OK", nullptr)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

void MenuDecideItem::selected()
{
    MenuItemFont::selected();
    
    InputModule::getInstance()->pushEvent(InputEvent::PRESS_DECIDE);
}

void MenuDecideItem::unselected()
{
    MenuItemFont::unselected();
    
    InputModule::getInstance()->pushEvent(InputEvent::RELEASE_DECIDE);
}