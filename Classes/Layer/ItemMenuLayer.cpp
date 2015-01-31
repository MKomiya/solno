//
//  ItemMenuLayer.cpp
//  solno
//
//  Created by S_Wyvern on 2015/01/28.
//
//

#include "ItemMenuLayer.h"

USING_NS_CC;

bool ItemMenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto s = Director::getInstance()->getWinSize();
    
    auto frame = Sprite::create("ui/ui_menu_item_frame.png");
    frame->setPosition(Point(s.width / 2.0f, s.height * 2.0f / 3.0f));
    addChild(frame);
    
    return true;
}