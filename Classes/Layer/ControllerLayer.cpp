//
//  ControllerLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2014/12/27.
//
//

#include "ControllerLayer.h"
#include "MenuArrowItem.h"

USING_NS_CC;

bool ControllerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto visible_size    = Director::getInstance()->getVisibleSize();
    auto texture = Director::getInstance()->getTextureCache()->addImage("ui/ui_common_frame.png");
    texture->setAliasTexParameters();
    
    auto frame = Sprite::createWithTexture(texture);
    frame->setPosition(Point(visible_size.width / 2.0f, visible_size.height / 2.0f));
    addChild(frame);
    
    auto button = MenuArrowItem::create("up");
    button->setPosition(Point(200, 200));
    auto button2 = MenuArrowItem::create("left");
    button2->setPosition(Point(160, 180));
    auto button3 = MenuArrowItem::create("down");
    button3->setPosition(Point(200, 160));
    auto button4 = MenuArrowItem::create("right");
    button4->setPosition(Point(240, 180));
    
    auto menu = Menu::create(button, button2, button3, button4, NULL);
    menu->setPosition(Point::ZERO);
    addChild(menu);
    
    return true;
}