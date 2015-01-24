//
//  MenuArrowItem.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/30.
//
//

#include "MenuArrowItem.h"
#include "InputModule.h"

USING_NS_CC;

MenuArrowItem::MenuArrowItem(std::string direction) :
_direction(direction) {}

MenuArrowItem* MenuArrowItem::create(std::string direction)
{
    auto pRet = new MenuArrowItem(direction);
    
    auto sprite = Sprite::create("ui/ui_arrow_button.png");
    
    /*
    if (direction == "right") {
        sprite->setAnchorPoint(Point(0, 0.5f));
        sprite->setRotation(90.0f);
    } else if (direction == "up") {
        sprite->setAnchorPoint(Point(0.5f, 0));
        sprite->setRotation(180.0f);
    } else if (direction == "left") {
        sprite->setAnchorPoint(Point(1.0f, 0.5f));
        sprite->setRotation(-90.0f);
    }*/
    
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

void MenuArrowItem::update(float dt)
{
    if (isSelected()) {
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
}