//
//  MenuArrowItem.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "MenuArrowItem.h"
#include "Dispatcher.h"

USING_NS_CC;

MenuArrowItem::MenuArrowItem(std::string direction) :
_direction(direction) {}

MenuArrowItem* MenuArrowItem::create(std::string direction)
{
    auto pRet = new MenuArrowItem(direction);
    auto sprite = Sprite::create("ui/ui_arrow_button.png");
    
    if (pRet && pRet->initWithNormalSprite(sprite, sprite, sprite, nullptr)) {
        pRet->autorelease();
        pRet->scheduleUpdate();
    } else {
        delete pRet;
        pRet = NULL;
    }
    
    pRet->setAnchorPoint(Point(0.5f, 0.5f));
    if (direction == "up") {
        pRet->setRotation(180.0f);
    } else if (direction == "right") {
        pRet->setRotation(-90.0f);
    } else if (direction == "left") {
        pRet->setRotation(90.0f);
    }
    
    return pRet;
}

void MenuArrowItem::selected()
{
    MenuItemSprite::selected();
}

void MenuArrowItem::unselected()
{
    MenuItemSprite::unselected();
    
    ArrowInputEvent event;
    if (_direction == "up") {
        event = ArrowInputEvent::RELEASE_UP;
    } else if (_direction == "right") {
        event = ArrowInputEvent::RELEASE_RIGHT;
    } else if (_direction == "down") {
        event = ArrowInputEvent::RELEASE_DOWN;
    } else if (_direction == "left") {
        event = ArrowInputEvent::RELEASE_LEFT;
    }
    
    auto dispatcher = Raciela::Dispatcher::getInstance();
    dispatcher->dispatch("input_arrow", event);
}

void MenuArrowItem::update(float dt)
{
    if (isSelected()) {
        ArrowInputEvent event;
        if (_direction == "up") {
            event = ArrowInputEvent::PRESS_UP;
        } else if (_direction == "right") {
            event = ArrowInputEvent::PRESS_RIGHT;
        } else if (_direction == "down") {
            event = ArrowInputEvent::PRESS_DOWN;
        } else if (_direction == "left") {
            event = ArrowInputEvent::PRESS_LEFT;
        }
        
        auto dispatcher = Raciela::Dispatcher::getInstance();
        dispatcher->dispatch("input_arrow", event);
    }
}