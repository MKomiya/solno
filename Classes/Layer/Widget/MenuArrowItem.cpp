//
//  MenuArrowItem.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "MenuArrowItem.h"
#include "InputModule.h"

MenuArrowItem::MenuArrowItem(std::string direction) :
_direction(direction) {}

MenuArrowItem* MenuArrowItem::create(std::string direction)
{
    auto pRet = new MenuArrowItem(direction);
    if (pRet && pRet->initWithString(direction.c_str(), NULL)) {
        pRet->autorelease();
    } else {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
}

void MenuArrowItem::selected()
{
    MenuItem::selected();
    CCLOG("selected");
    
    InputModule::getInstance()->setInputCommandByString(_direction);
}

void MenuArrowItem::unselected()
{
    MenuItem::unselected();
    CCLOG("unselected");

    InputModule::getInstance()->setInputCommand(InputCommand::NOTHING);
}
