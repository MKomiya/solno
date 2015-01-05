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
    
    InputEvent event;
    if (_direction == "up") {
        event = InputEvent::PRESS_UP;
    } else if (_direction == "right") {
        event = InputEvent::PRESS_RIGHT;
    } else if (_direction == "down") {
        event = InputEvent::PRESS_DOWN;
    } else if (_direction == "left") {
        event = InputEvent::PRESS_LEFT;
    }
    
    InputModule::getInstance()->pushEvent(event);
}

void MenuArrowItem::unselected()
{
    MenuItem::unselected();
    CCLOG("unselected");
    
    InputEvent event;
    if (_direction == "up") {
        event = InputEvent::RELEASE_UP;
    } else if (_direction == "right") {
        event = InputEvent::RELEASE_RIGHT;
    } else if (_direction == "down") {
        event = InputEvent::RELEASE_DOWN;
    } else if (_direction == "left") {
        event = InputEvent::RELEASE_LEFT;
    }
    
    InputModule::getInstance()->pushEvent(event);
}
